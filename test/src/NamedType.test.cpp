#include "cpp/NamedType.hpp"
#include "doctest.h"

#include "cpp/Warning.hpp"
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>

template <typename T>
decltype(auto) tee(T&& value)
{
    std::cout << value << '\n';
    return std::forward<T>(value);
}

using Meter = cpp::NamedType<unsigned long long, struct MeterParameter, cpp::Addable, cpp::Comparable>;
Meter operator"" _meter(unsigned long long value) { return Meter(value); }
//Meter operator"" _meter(long double value) { return Meter(value); }

using Width  = cpp::NamedType<Meter, struct WidthParameter>;
using Height = cpp::NamedType<Meter, struct HeightParameter>;

class Rectangle
{
public:
    Rectangle(Width width, Height height)
        : width_(width.get())
        , height_(height.get())
    {}
    Meter getWidth() const { return width_; }
    Meter getHeight() const { return height_; }

private:
    Meter width_;
    Meter height_;
};

TEST_CASE("Basic usage")
{
    Rectangle r(Width(10_meter), Height(12_meter));
    CHECK_EQ(r.getWidth().get(), 10);
    CHECK_EQ(r.getHeight().get(), 12);
}

using NameRef = cpp::NamedType<std::string&, struct NameRefParameter>;

void changeValue(NameRef name) { name.get() = "value2"; }

TEST_CASE("Passing a strong reference")
{
    std::string value = "value1";
    changeValue(NameRef(value));
    CHECK_EQ(value, "value2");
}

TEST_CASE("Construction of NamedType::ref from the underlying type")
{
    using StrongInt = cpp::NamedType<int, struct StrongIntTag>;
    auto addOne     = [](StrongInt::ref si) { ++(si.get()); };

    int i = 42;
    addOne(StrongInt::ref(i));
    CHECK_EQ(i, 43);
}

TEST_CASE("Implicit conversion of NamedType to NamedType::ref")
{
    using StrongInt = cpp::NamedType<int, struct StrongIntTag>;
    auto addOne     = [](StrongInt::ref si) { ++(si.get()); };

    StrongInt i(42);
    addOne(i);
    CHECK_EQ(i.get(), 43);

    StrongInt j(42);
    addOne(StrongInt::ref(j));
    CHECK_EQ(j.get(), 43);
}

template <typename Function>
using Comparator = cpp::NamedType<Function, struct ComparatorParameter>;

template <typename Function>
std::string performAction(Comparator<Function> comp)
{
    return comp.get()();
}

TEST_CASE("Strong generic type")
{
    REQUIRE(performAction(cpp::make_named<Comparator>([]() { return std::string("compare"); })) == "compare");
}

TEST_CASE("Addable")
{
    using AddableType = cpp::NamedType<int, struct AddableTag, cpp::Addable>;
    AddableType s1(12);
    AddableType s2(10);
    CHECK_EQ((s1 + s2).get(), 22);
    s1 += s2;
    CHECK_EQ(s1.get(), 22);
}

TEST_CASE("Subtractable")
{
    using SubtractableType = cpp::NamedType<int, struct SubtractableTag, cpp::Subtractable>;
    SubtractableType s1(12);
    SubtractableType s2(10);
    CHECK_EQ((s1 - s2).get(), 2);
    s1 -= s2;
    CHECK_EQ(s1.get(), 2);
}

TEST_CASE("Multiplicable")
{
    using MultiplicableType = cpp::NamedType<int, struct MultiplicableTag, cpp::Multiplicable>;
    MultiplicableType s1(12);
    MultiplicableType s2(10);
    CHECK_EQ((s1 * s2).get(), 120);
    s1 *= s2;
    CHECK_EQ(s1.get(), 120);
}

TEST_CASE("Divisible")
{
    using DivisibleType = cpp::NamedType<int, struct DivisibleTag, cpp::Divisible>;
    DivisibleType s1(120);
    DivisibleType s2(10);
    CHECK_EQ((s1 / s2).get(), 12);
    s1 /= s2;
    CHECK_EQ(s1.get(), 12);
}

TEST_CASE("Modulable")
{
    using ModulableType = cpp::NamedType<int, struct ModulableTag, cpp::Modulable>;
    ModulableType s1(5);
    ModulableType s2(2);
    CHECK_EQ((s1 % s2).get(), 1);
    s1 %= s2;
    CHECK_EQ(s1.get(), 1);
}

TEST_CASE("BitWiseInvertable")
{
    using BitWiseInvertableType = cpp::NamedType<int, struct BitWiseInvertableTag, cpp::BitWiseInvertable>;
    BitWiseInvertableType s1(13);
    CHECK_EQ((~s1).get(), (~13));
}

TEST_CASE("BitWiseAndable")
{
    using BitWiseAndableType = cpp::NamedType<int, struct BitWiseAndableTag, cpp::BitWiseAndable>;
    BitWiseAndableType s1(2);
    BitWiseAndableType s2(64);
    CHECK_EQ((s1 & s2).get(), (2 & 64));
    s1 &= s2;
    CHECK_EQ(s1.get(), (2 & 64));
}

TEST_CASE("BitWiseOrable")
{
    using BitWiseOrableType = cpp::NamedType<int, struct BitWiseOrableTag, cpp::BitWiseOrable>;
    BitWiseOrableType s1(2);
    BitWiseOrableType s2(64);
    CHECK_EQ((s1 | s2).get(), (2 | 64));
    s1 |= s2;
    CHECK_EQ(s1.get(), (2 | 64));
}

TEST_CASE("BitWiseXorable")
{
    using BitWiseXorableType = cpp::NamedType<int, struct BitWiseXorableTag, cpp::BitWiseXorable>;
    BitWiseXorableType s1(2);
    BitWiseXorableType s2(64);
    CHECK_EQ((s1 ^ s2).get(), (2 ^ 64));
    s1 ^= s2;
    CHECK_EQ(s1.get(), (2 ^ 64));
}

TEST_CASE("BitWiseLeftShiftable")
{
    using BitWiseLeftShiftableType = cpp::NamedType<int, struct BitWiseLeftShiftableTag, cpp::BitWiseLeftShiftable>;
    BitWiseLeftShiftableType s1(2);
    BitWiseLeftShiftableType s2(3);
    CHECK_EQ((s1 << s2).get(), (2 << 3));
    s1 <<= s2;
    CHECK_EQ(s1.get(), (2 << 3));
}

TEST_CASE("BitWiseRightShiftable")
{
    using BitWiseRightShiftableType = cpp::NamedType<int, struct BitWiseRightShiftableTag, cpp::BitWiseRightShiftable>;
    BitWiseRightShiftableType s1(2);
    BitWiseRightShiftableType s2(3);
    CHECK_EQ((s1 >> s2).get(), (2 >> 3));
    s1 >>= s2;
    CHECK_EQ(s1.get(), (2 >> 3));
}

TEST_CASE("Negatable")
{
    using NegatableType = cpp::NamedType<int, struct NegatableTag, cpp::Negatable>;
    NegatableType value(10);
    CHECK_EQ((-value).get(), -10);
}

TEST_CASE("Comparable")
{
    CHECK((10_meter == 10_meter));
    CHECK(!(10_meter == 11_meter));
    CHECK((10_meter != 11_meter));
    CHECK(!(10_meter != 10_meter));
    CHECK((10_meter < 11_meter));
    CHECK(!(10_meter < 10_meter));
    CHECK((10_meter <= 10_meter));
    CHECK((10_meter <= 11_meter));
    CHECK(!(10_meter <= 9_meter));
    CHECK((11_meter > 10_meter));
    CHECK(!(10_meter > 11_meter));
    CHECK((11_meter >= 10_meter));
    CHECK((10_meter >= 10_meter));
    CHECK(!(9_meter >= 10_meter));
}

TEST_CASE("ConvertibleWithOperator")
{
    struct B
    {
        B(int x_)
            : x(x_)
        {}
        int x;
    };

    struct A
    {
        A(int x_)
            : x(x_)
        {}
            operator B() const { return B(x); }
        int x;
    };

    using StrongA = cpp::NamedType<A, struct StrongATag, cpp::ImplicitlyConvertibleTo<B>::templ>;
    StrongA strongA(A(42));
    B       b = strongA;
    CHECK_EQ(b.x, 42);
}

TEST_CASE("ConvertibleWithConstructor")
{
    struct A
    {
        A(int x_)
            : x(x_)
        {}
        int x;
    };

    struct B
    {
        B(A a)
            : x(a.x)
        {}
        int x;
    };

    using StrongA = cpp::NamedType<A, struct StrongATag, cpp::ImplicitlyConvertibleTo<B>::templ>;
    StrongA strongA(A(42));
    B       b = strongA;
    CHECK_EQ(b.x, 42);
}

TEST_CASE("ConvertibleToItself")
{
    using MyInt = cpp::NamedType<int, struct MyIntTag, cpp::ImplicitlyConvertibleTo<int>::templ>;
    MyInt myInt(42);
    int   i = myInt;
    CHECK_EQ(i, 42);
}

TEST_CASE("Hash")
{
    using SerialNumber = cpp::NamedType<std::string, struct SerialNumberTag, cpp::Comparable, cpp::Hashable>;

    std::unordered_map<SerialNumber, int> hashMap = {{SerialNumber{"AA11"}, 10}, {SerialNumber{"BB22"}, 20}};
    SerialNumber                          cc33{"CC33"};
    hashMap[cc33] = 30;
    CHECK_EQ(hashMap[SerialNumber{"AA11"}], 10);
    CHECK_EQ(hashMap[SerialNumber{"BB22"}], 20);
    CHECK_EQ(hashMap[cc33], 30);
}

struct testFunctionCallable_A
{
    testFunctionCallable_A(int x_)
        : x(x_)
    {}
    testFunctionCallable_A(testFunctionCallable_A const&) =
            delete; // ensures that passing the argument to a function doesn't make a copy
    testFunctionCallable_A(testFunctionCallable_A&&) = default;
    testFunctionCallable_A& operator+=(testFunctionCallable_A const& other)
    {
        x += other.x;
        return *this;
    }
    int x;
};

testFunctionCallable_A operator+(testFunctionCallable_A const& a1, testFunctionCallable_A const& a2)
{
    return testFunctionCallable_A(a1.x + a2.x);
}

bool operator==(testFunctionCallable_A const& a1, testFunctionCallable_A const& a2) { return a1.x == a2.x; }

TEST_CASE("Function callable")
{
    using A              = testFunctionCallable_A;
    auto functionTakingA = [](A const& a) { return a.x; };

    using StrongA = cpp::NamedType<A, struct StrongATag, cpp::FunctionCallable>;
    StrongA       strongA(A(42));
    const StrongA constStrongA(A(42));
    CHECK_EQ(functionTakingA(strongA), 42);
    CHECK_EQ(functionTakingA(constStrongA), 42);
    CHECK_EQ(strongA + strongA, 84);
}

TEST_CASE("Method callable")
{
    class A
    {
    public:
        A(int x_)
            : x(x_)
        {}
        A(A const&) = delete; // ensures that invoking a method doesn't make a copy
        A(A&&)      = default;

        int method() { return x; }
        int constMethod() const { return x; }

    private:
        int x;
    };

    using StrongA = cpp::NamedType<A, struct StrongATag, cpp::MethodCallable>;
    StrongA       strongA(A(42));
    const StrongA constStrongA(A((42)));
    CHECK_EQ(strongA->method(), 42);
    CHECK_EQ(constStrongA->constMethod(), 42);
}

TEST_CASE("Callable")
{
    class A
    {
    public:
        A(int x_)
            : x(x_)
        {}
        A(A const&) = delete; // ensures that invoking a method or function doesn't make a copy
        A(A&&)      = default;

        int method() { return x; }
        int constMethod() const { return x; }

    private:
        int x;
    };

    auto functionTakingA = [](A const& a) { return a.constMethod(); };

    using StrongA = cpp::NamedType<A, struct StrongATag, cpp::Callable>;
    StrongA       strongA(A(42));
    const StrongA constStrongA(A((42)));
    REQUIRE(functionTakingA(strongA) == 42);
    REQUIRE(strongA->method() == 42);
    REQUIRE(constStrongA->constMethod() == 42);
}

TEST_CASE("Named arguments")
{
    using FirstName = cpp::NamedType<std::string, struct FirstNameTag>;
    using LastName  = cpp::NamedType<std::string, struct LastNameTag>;
    static const FirstName::argument firstName;
    static const LastName::argument  lastName;
    auto                             getFullName = [](const FirstName& first_name, const LastName& last_name) {
        return first_name.get() + last_name.get();
    };

    auto fullName = getFullName(firstName = "James", lastName = "Bond");
    REQUIRE(fullName == "JamesBond");
}

TEST_CASE("Empty base class optimization") { CHECK_EQ(sizeof(Meter), sizeof(Meter::type)); }

using strong_float = cpp::NamedType<float, struct FloatTag>;

TEST_CASE("Default constructible")
{
    strong_float f1;
    strong_float f2{};
}

struct throw_on_construction
{
    throw_on_construction() { throw 42; }

    throw_on_construction(int) { throw "exception"; }
};

using C = cpp::NamedType<throw_on_construction, struct throwTag>;

TEST_CASE("noexcept")
{
    CHECK_UNARY(noexcept(strong_float{}));
    CHECK_UNARY_FALSE(noexcept(C{}));

    CHECK_UNARY(noexcept(strong_float(3.14f)));
    CHECK_UNARY_FALSE(noexcept(C{5}));
}

using strong_bool = cpp::NamedType<bool, struct BoolTag>;

TEST_CASE("constexpr") { static_assert(strong_bool{true}.get()); }

TEST_CASE("Arithmetic")
{
    using strong_integer = cpp::NamedType<int, struct IntTag, cpp::Arithmetic>;
    strong_integer a{1};
    strong_integer b{2};

    CHECK_EQ((a + b).get(), 3);

    a += b;
    CHECK_EQ(a.get(), 3);

    CHECK_EQ((a - b).get(), 1);

    a -= b;
    CHECK_EQ(a.get(), 1);

    a.get() = 5;
    CHECK_EQ((a * b).get(), 10);

    a *= b;
    CHECK_EQ(a.get(), 10);

    CHECK_EQ((a / b).get(), 5);

    a /= b;
    CHECK_EQ(a.get(), 5);

    a.get() = 5;
    b.get() = 2;
    CHECK_EQ((a % b).get(), 1);

    a %= b;
    CHECK_EQ(a.get(), 1);
}
