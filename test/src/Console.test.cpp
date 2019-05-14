// These tests are based on Abhinav Gauniyal's tests from rang library <https://github.com/agauniyal/rang>
// Original file <https://github.com/agauniyal/rang/blob/master/test/test.cpp>

#include "cpp/Console.hpp"
#include "cpp/OS.hpp"
#include "cpp/Warning.hpp"
#include "doctest.h"

#include <fstream>
#include <string>

CPP_CLANG_SUPPRESS_WARNING_PUSH
CPP_CLANG_SUPPRESS_WARNING("-Wexit-time-destructors")
CPP_CLANG_SUPPRESS_WARNING("-Wglobal-constructors")

const std::string str      = "Hello World";
const std::string fileName = "Output.txt";

const std::wstring strW      = L"Hello World";
const std::string  fileNameW = "OutputW.txt";

CPP_CLANG_SUPPRESS_WARNING_POP

TEST_CASE("printing with control::Off and cout")
{
    cpp::setControlMode(cpp::control::Off);

    SUBCASE("WinTerm = Native")
    {
        cpp::setWinTermMode(cpp::winTerm::Native);

        std::ofstream   out(fileName);
        std::streambuf* coutbuf = std::cout.rdbuf();
        std::cout.rdbuf(out.rdbuf());
        std::cout << cpp::fg::blue << str << cpp::style::reset;
        std::cout.rdbuf(coutbuf);
        out.close();

        std::ifstream in(fileName);
        std::string   output;
        std::getline(in, output);

        REQUIRE(str == output);
    }

    SUBCASE("WinTerm = Auto")
    {
        cpp::setWinTermMode(cpp::winTerm::Auto);

        std::ofstream   out(fileName);
        std::streambuf* coutbuf = std::cout.rdbuf();
        std::cout.rdbuf(out.rdbuf());
        std::cout << cpp::fg::blue << str << cpp::style::reset;
        std::cout.rdbuf(coutbuf);
        out.close();

        std::ifstream in(fileName);
        std::string   output;
        std::getline(in, output);

        REQUIRE(str == output);
    }

    SUBCASE("WinTerm = Ansi")
    {
        cpp::setWinTermMode(cpp::winTerm::Ansi);

        std::ofstream   out(fileName);
        std::streambuf* coutbuf = std::cout.rdbuf();
        std::cout.rdbuf(out.rdbuf());
        std::cout << cpp::fg::blue << str << cpp::style::reset;
        std::cout.rdbuf(coutbuf);
        out.close();

        std::ifstream in(fileName);
        std::string   output;
        std::getline(in, output);

        REQUIRE(str == output);
    }
}

TEST_CASE("printing with control::Force and cout")
{
    cpp::setControlMode(cpp::control::Force);

    SUBCASE("WinTerm = Native")
    {
        cpp::setWinTermMode(cpp::winTerm::Native);

        std::ofstream   out(fileName);
        std::streambuf* coutbuf = std::cout.rdbuf();
        std::cout.rdbuf(out.rdbuf());
        std::cout << cpp::fg::blue << str << cpp::style::reset;
        std::cout.rdbuf(coutbuf);
        out.close();

        std::ifstream in(fileName);
        std::string   output;
        std::getline(in, output);

#if CPP_OS_IS(CPP_OS_LINUX) || CPP_OS_IS(CPP_OS_MACOS)
        REQUIRE(str != output);
        REQUIRE(str.size() < output.size());
#elif CPP_OS_IS(CPP_OS_WINDOWS)
        REQUIRE(str == output);
#endif
    }

    SUBCASE("WinTerm = Ansi")
    {
        cpp::setWinTermMode(cpp::winTerm::Ansi);

        std::ofstream   out(fileName);
        std::streambuf* coutbuf = std::cout.rdbuf();
        std::cout.rdbuf(out.rdbuf());
        std::cout << cpp::fg::blue << str << cpp::style::reset;
        std::cout.rdbuf(coutbuf);
        out.close();

        std::ifstream in(fileName);
        std::string   output;
        std::getline(in, output);

        REQUIRE(str != output);
        REQUIRE(str.size() < output.size());
    }
}

TEST_CASE("printing with control::Off and cerr")
{
    cpp::setControlMode(cpp::control::Off);

    SUBCASE("WinTerm = Native")
    {
        cpp::setWinTermMode(cpp::winTerm::Native);

        std::ofstream   out(fileName);
        std::streambuf* cerrbuf = std::cerr.rdbuf();
        std::cerr.rdbuf(out.rdbuf());
        std::cerr << cpp::fg::blue << str << cpp::style::reset;
        std::cerr.rdbuf(cerrbuf);
        out.close();

        std::ifstream in(fileName);
        std::string   output;
        std::getline(in, output);

        REQUIRE(str == output);
    }

    SUBCASE("WinTerm = Auto")
    {
        cpp::setWinTermMode(cpp::winTerm::Auto);

        std::ofstream   out(fileName);
        std::streambuf* cerrbuf = std::cerr.rdbuf();
        std::cerr.rdbuf(out.rdbuf());
        std::cerr << cpp::fg::blue << str << cpp::style::reset;
        std::cerr.rdbuf(cerrbuf);
        out.close();

        std::ifstream in(fileName);
        std::string   output;
        std::getline(in, output);

        REQUIRE(str == output);
    }

    SUBCASE("WinTerm = Ansi")
    {
        cpp::setWinTermMode(cpp::winTerm::Ansi);

        std::ofstream   out(fileName);
        std::streambuf* cerrbuf = std::cerr.rdbuf();
        std::cerr.rdbuf(out.rdbuf());
        std::cerr << cpp::fg::blue << str << cpp::style::reset;
        std::cerr.rdbuf(cerrbuf);
        out.close();

        std::ifstream in(fileName);
        std::string   output;
        std::getline(in, output);

        REQUIRE(str == output);
    }
}

TEST_CASE("printing with control::Force and cerr")
{
    cpp::setControlMode(cpp::control::Force);

    SUBCASE("WinTerm = Native")
    {
        cpp::setWinTermMode(cpp::winTerm::Native);

        std::ofstream   out(fileName);
        std::streambuf* cerrbuf = std::cerr.rdbuf();
        std::cerr.rdbuf(out.rdbuf());
        std::cerr << cpp::fg::blue << str << cpp::style::reset;
        std::cerr.rdbuf(cerrbuf);
        out.close();

        std::ifstream in(fileName);
        std::string   output;
        std::getline(in, output);

#if CPP_OS_IS(CPP_OS_LINUX) || CPP_OS_IS(CPP_OS_MACOS)
        REQUIRE(str != output);
        REQUIRE(str.size() < output.size());
#elif CPP_OS_IS(CPP_OS_WINDOWS)
        REQUIRE(str == output);
#endif
    }

    SUBCASE("WinTerm = Ansi")
    {
        cpp::setWinTermMode(cpp::winTerm::Ansi);

        std::ofstream   out(fileName);
        std::streambuf* cerrbuf = std::cerr.rdbuf();
        std::cerr.rdbuf(out.rdbuf());
        std::cerr << cpp::fg::blue << str << cpp::style::reset;
        std::cerr.rdbuf(cerrbuf);
        out.close();

        std::ifstream in(fileName);
        std::string   output;
        std::getline(in, output);

        REQUIRE(str != output);
        REQUIRE(str.size() < output.size());
    }
}

TEST_CASE("printing with control::Off and clog")
{
    cpp::setControlMode(cpp::control::Off);

    SUBCASE("WinTerm = Native")
    {
        cpp::setWinTermMode(cpp::winTerm::Native);

        std::ofstream   out(fileName);
        std::streambuf* clogbuf = std::clog.rdbuf();
        std::clog.rdbuf(out.rdbuf());
        std::clog << cpp::fg::blue << str << cpp::style::reset;
        std::clog.rdbuf(clogbuf);
        out.close();

        std::ifstream in(fileName);
        std::string   output;
        std::getline(in, output);

        REQUIRE(str == output);
    }

    SUBCASE("WinTerm = Auto")
    {
        cpp::setWinTermMode(cpp::winTerm::Auto);

        std::ofstream   out(fileName);
        std::streambuf* clogbuf = std::clog.rdbuf();
        std::clog.rdbuf(out.rdbuf());
        std::clog << cpp::fg::blue << str << cpp::style::reset;
        std::clog.rdbuf(clogbuf);
        out.close();

        std::ifstream in(fileName);
        std::string   output;
        std::getline(in, output);

        REQUIRE(str == output);
    }

    SUBCASE("WinTerm = Ansi")
    {
        cpp::setWinTermMode(cpp::winTerm::Ansi);

        std::ofstream   out(fileName);
        std::streambuf* clogbuf = std::clog.rdbuf();
        std::clog.rdbuf(out.rdbuf());
        std::clog << cpp::fg::blue << str << cpp::style::reset;
        std::clog.rdbuf(clogbuf);
        out.close();

        std::ifstream in(fileName);
        std::string   output;
        std::getline(in, output);

        REQUIRE(str == output);
    }
}

TEST_CASE("printing with control::Force and clog")
{
    cpp::setControlMode(cpp::control::Force);

    SUBCASE("WinTerm = Native")
    {
        cpp::setWinTermMode(cpp::winTerm::Native);

        std::ofstream   out(fileName);
        std::streambuf* clogbuf = std::clog.rdbuf();
        std::clog.rdbuf(out.rdbuf());
        std::clog << cpp::fg::blue << str << cpp::style::reset;
        std::clog.rdbuf(clogbuf);
        out.close();

        std::ifstream in(fileName);
        std::string   output;
        std::getline(in, output);

#if CPP_OS_IS(CPP_OS_LINUX) || CPP_OS_IS(CPP_OS_MACOS)
        REQUIRE(str != output);
        REQUIRE(str.size() < output.size());
#elif CPP_OS_IS(CPP_OS_WINDOWS)
        REQUIRE(str == output);
#endif
    }

    SUBCASE("WinTerm = Ansi")
    {
        cpp::setWinTermMode(cpp::winTerm::Ansi);

        std::ofstream   out(fileName);
        std::streambuf* clogbuf = std::clog.rdbuf();
        std::clog.rdbuf(out.rdbuf());
        std::clog << cpp::fg::blue << str << cpp::style::reset;
        std::clog.rdbuf(clogbuf);
        out.close();

        std::ifstream in(fileName);
        std::string   output;
        std::getline(in, output);

        REQUIRE(str != output);
        REQUIRE(str.size() < output.size());
    }
}

// Tests with wide characters
TEST_CASE("printing with control::Off and wcout")
{
    cpp::setControlMode(cpp::control::Off);

    SUBCASE("WinTerm = Native")
    {
        cpp::setWinTermMode(cpp::winTerm::Native);

        std::wofstream   out(fileNameW);
        std::wstreambuf* coutbuf = std::wcout.rdbuf();
        std::wcout.rdbuf(out.rdbuf());
        std::wcout << cpp::fg::blue << strW << cpp::style::reset;
        std::wcout.rdbuf(coutbuf);
        out.close();

        std::wifstream in(fileNameW);
        std::wstring   output;
        std::getline(in, output);

        REQUIRE(strW == output);
    }

    SUBCASE("WinTerm = Auto")
    {
        cpp::setWinTermMode(cpp::winTerm::Auto);

        std::wofstream   out(fileNameW);
        std::wstreambuf* coutbuf = std::wcout.rdbuf();
        std::wcout.rdbuf(out.rdbuf());
        std::wcout << cpp::fg::blue << strW << cpp::style::reset;
        std::wcout.rdbuf(coutbuf);
        out.close();

        std::wifstream in(fileNameW);
        std::wstring   output;
        std::getline(in, output);

        REQUIRE(strW == output);
    }

    SUBCASE("WinTerm = Ansi")
    {
        cpp::setWinTermMode(cpp::winTerm::Ansi);

        std::wofstream   out(fileNameW);
        std::wstreambuf* coutbuf = std::wcout.rdbuf();
        std::wcout.rdbuf(out.rdbuf());
        std::wcout << cpp::fg::blue << strW << cpp::style::reset;
        std::wcout.rdbuf(coutbuf);
        out.close();

        std::wifstream in(fileNameW);
        std::wstring   output;
        std::getline(in, output);

        REQUIRE(strW == output);
    }
}

TEST_CASE("printing with control::Force and wcout")
{
    cpp::setControlMode(cpp::control::Force);

    SUBCASE("WinTerm = Native")
    {
        cpp::setWinTermMode(cpp::winTerm::Native);

        std::wofstream   out(fileNameW);
        std::wstreambuf* coutbuf = std::wcout.rdbuf();
        std::wcout.rdbuf(out.rdbuf());
        std::wcout << cpp::fg::blue << strW << cpp::style::reset;
        std::wcout.rdbuf(coutbuf);
        out.close();

        std::wifstream in(fileNameW);
        std::wstring   output;
        std::getline(in, output);

#if CPP_OS_IS(CPP_OS_LINUX) || CPP_OS_IS(CPP_OS_MACOS)
        REQUIRE(strW != output);
        REQUIRE(strW.size() < output.size());
#elif CPP_OS_IS(CPP_OS_WINDOWS)
        REQUIRE(strW == output);
#endif
    }

    SUBCASE("WinTerm = Ansi")
    {
        cpp::setWinTermMode(cpp::winTerm::Ansi);

        std::wofstream   out(fileNameW);
        std::wstreambuf* coutbuf = std::wcout.rdbuf();
        std::wcout.rdbuf(out.rdbuf());
        std::wcout << cpp::fg::blue << strW << cpp::style::reset;
        std::wcout.rdbuf(coutbuf);
        out.close();

        std::wifstream in(fileNameW);
        std::wstring   output;
        std::getline(in, output);

        REQUIRE(strW != output);
        REQUIRE(strW.size() < output.size());
    }
}

TEST_CASE("printing with control::Off and wcerr")
{
    cpp::setControlMode(cpp::control::Off);

    SUBCASE("WinTerm = Native")
    {
        cpp::setWinTermMode(cpp::winTerm::Native);

        std::wofstream   out(fileNameW);
        std::wstreambuf* cerrbuf = std::wcerr.rdbuf();
        std::wcerr.rdbuf(out.rdbuf());
        std::wcerr << cpp::fg::blue << strW << cpp::style::reset;
        std::wcerr.rdbuf(cerrbuf);
        out.close();

        std::wifstream in(fileNameW);
        std::wstring   output;
        std::getline(in, output);

        REQUIRE(strW == output);
    }

    SUBCASE("WinTerm = Auto")
    {
        cpp::setWinTermMode(cpp::winTerm::Auto);

        std::wofstream   out(fileNameW);
        std::wstreambuf* cerrbuf = std::wcerr.rdbuf();
        std::wcerr.rdbuf(out.rdbuf());
        std::wcerr << cpp::fg::blue << strW << cpp::style::reset;
        std::wcerr.rdbuf(cerrbuf);
        out.close();

        std::wifstream in(fileNameW);
        std::wstring   output;
        std::getline(in, output);

        REQUIRE(strW == output);
    }

    SUBCASE("WinTerm = Ansi")
    {
        cpp::setWinTermMode(cpp::winTerm::Ansi);

        std::wofstream   out(fileNameW);
        std::wstreambuf* cerrbuf = std::wcerr.rdbuf();
        std::wcerr.rdbuf(out.rdbuf());
        std::wcerr << cpp::fg::blue << strW << cpp::style::reset;
        std::wcerr.rdbuf(cerrbuf);
        out.close();

        std::wifstream in(fileNameW);
        std::wstring   output;
        std::getline(in, output);

        REQUIRE(strW == output);
    }
}

TEST_CASE("printing with control::Force and wcerr")
{
    cpp::setControlMode(cpp::control::Force);

    SUBCASE("WinTerm = Native")
    {
        cpp::setWinTermMode(cpp::winTerm::Native);

        std::wofstream   out(fileNameW);
        std::wstreambuf* cerrbuf = std::wcerr.rdbuf();
        std::wcerr.rdbuf(out.rdbuf());
        std::wcerr << cpp::fg::blue << strW << cpp::style::reset;
        std::wcerr.rdbuf(cerrbuf);
        out.close();

        std::wifstream in(fileNameW);
        std::wstring   output;
        std::getline(in, output);

#if CPP_OS_IS(CPP_OS_LINUX) || CPP_OS_IS(CPP_OS_MACOS)
        REQUIRE(strW != output);
        REQUIRE(strW.size() < output.size());
#elif CPP_OS_IS(CPP_OS_WINDOWS)
        REQUIRE(strW == output);
#endif
    }

    SUBCASE("WinTerm = Ansi")
    {
        cpp::setWinTermMode(cpp::winTerm::Ansi);

        std::wofstream   out(fileNameW);
        std::wstreambuf* cerrbuf = std::wcerr.rdbuf();
        std::wcerr.rdbuf(out.rdbuf());
        std::wcerr << cpp::fg::blue << strW << cpp::style::reset;
        std::wcerr.rdbuf(cerrbuf);
        out.close();

        std::wifstream in(fileNameW);
        std::wstring   output;
        std::getline(in, output);

        REQUIRE(strW != output);
        REQUIRE(strW.size() < output.size());
    }
}

TEST_CASE("printing with control::Off and wclog")
{
    cpp::setControlMode(cpp::control::Off);

    SUBCASE("WinTerm = Native")
    {
        cpp::setWinTermMode(cpp::winTerm::Native);

        std::wofstream   out(fileNameW);
        std::wstreambuf* clogbuf = std::wclog.rdbuf();
        std::wclog.rdbuf(out.rdbuf());
        std::wclog << cpp::fg::blue << strW << cpp::style::reset;
        std::wclog.rdbuf(clogbuf);
        out.close();

        std::wifstream in(fileNameW);
        std::wstring   output;
        std::getline(in, output);

        REQUIRE(strW == output);
    }

    SUBCASE("WinTerm = Auto")
    {
        cpp::setWinTermMode(cpp::winTerm::Auto);

        std::wofstream   out(fileNameW);
        std::wstreambuf* clogbuf = std::wclog.rdbuf();
        std::wclog.rdbuf(out.rdbuf());
        std::wclog << cpp::fg::blue << strW << cpp::style::reset;
        std::wclog.rdbuf(clogbuf);
        out.close();

        std::wifstream in(fileNameW);
        std::wstring   output;
        std::getline(in, output);

        REQUIRE(strW == output);
    }

    SUBCASE("WinTerm = Ansi")
    {
        cpp::setWinTermMode(cpp::winTerm::Ansi);

        std::wofstream   out(fileNameW);
        std::wstreambuf* clogbuf = std::wclog.rdbuf();
        std::wclog.rdbuf(out.rdbuf());
        std::wclog << cpp::fg::blue << strW << cpp::style::reset;
        std::wclog.rdbuf(clogbuf);
        out.close();

        std::wifstream in(fileNameW);
        std::wstring   output;
        std::getline(in, output);

        REQUIRE(strW == output);
    }
}

TEST_CASE("printing with control::Force and wclog")
{
    cpp::setControlMode(cpp::control::Force);

    SUBCASE("WinTerm = Native")
    {
        cpp::setWinTermMode(cpp::winTerm::Native);

        std::wofstream   out(fileNameW);
        std::wstreambuf* clogbuf = std::wclog.rdbuf();
        std::wclog.rdbuf(out.rdbuf());
        std::wclog << cpp::fg::blue << strW << cpp::style::reset;
        std::wclog.rdbuf(clogbuf);
        out.close();

        std::wifstream in(fileNameW);
        std::wstring   output;
        std::getline(in, output);

#if CPP_OS_IS(CPP_OS_LINUX) || CPP_OS_IS(CPP_OS_MACOS)
        REQUIRE(strW != output);
        REQUIRE(strW.size() < output.size());
#elif CPP_OS_IS(CPP_OS_WINDOWS)
        REQUIRE(strW == output);
#endif
    }

    SUBCASE("WinTerm = Ansi")
    {
        cpp::setWinTermMode(cpp::winTerm::Ansi);

        std::wofstream   out(fileNameW);
        std::wstreambuf* clogbuf = std::wclog.rdbuf();
        std::wclog.rdbuf(out.rdbuf());
        std::wclog << cpp::fg::blue << strW << cpp::style::reset;
        std::wclog.rdbuf(clogbuf);
        out.close();

        std::wifstream in(fileNameW);
        std::wstring   output;
        std::getline(in, output);

        REQUIRE(strW != output);
        REQUIRE(strW.size() < output.size());
    }
}
