#include "cpp/Console.hpp"
#include "cpp/Warning.hpp"
#include <chrono>

CPP_MSVC_SUPPRESS_WARNING_PUSH
CPP_MSVC_SUPPRESS_WARNING(
        5039) // 'x': pointer or reference to potentially throwing function passed to extern C function under -EHc. Undefined behavior may occur if this function throws an exception.
#include <thread>
CPP_MSVC_SUPPRESS_WARNING_POP

using seconds = std::chrono::duration<int, std::ratio<1>>;

int main()
{
#if defined(_UNICODE) || defined(UNICODE)
    std::wcout << cpp::cursor::setVisible(false);
    std::wcout << "Hidden for wcout!" << std::endl;
    std::this_thread::sleep_for(seconds(2));
    std::wcout << cpp::cursor::setVisible(true) << std::endl;
    std::wcout << "Shown for wcout!" << std::endl;
    std::wcout << "Moving cursor to 10-10: ";
    std::wcout << cpp::cursor::setPos(10, 10) << "Done!\n";
#else
    std::cout << cpp::cursor::setVisible(false);
    std::cout << "Hidden for cout!" << std::endl;
    std::this_thread::sleep_for(seconds(2));
    std::cout << cpp::cursor::setVisible(true) << std::endl;
    std::cout << "Shown for cout!" << std::endl;
    std::cout << "Moving cursor to 10-10: ";
    std::cout << cpp::cursor::setPos(10, 10) << "Done!\n";
#endif
}
