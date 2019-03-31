// This example is taken from Abhinav Gauniyal' rang library <https://github.com/agauniyal/rang>
// original file <https://github.com/agauniyal/rang/blob/master/test/colorTest.cpp>

#include "cpp/Console.hpp"
#include <string>

void printHeading(const std::string& heading)
{
    std::cout << '\n'
              << cpp::style::reset << heading << cpp::style::reset << cpp::bg::reset << cpp::fg::reset << std::endl;
}

template <typename CharT>
void test_colors(std::basic_ostream<CharT>& os, const cpp::winTerm opt)
{
    cpp::setWinTermMode(opt);

    printHeading("Text style Test:");
    os << cpp::style::bold << " Bold " << cpp::style::reset;
    os << cpp::style::italic << " Italic " << cpp::style::reset;
    os << cpp::style::underline << " Underlined " << cpp::style::reset;
    os << cpp::style::dim << " Dim " << cpp::style::reset;
    os << cpp::style::conceal << " Conceal " << cpp::style::reset;
    os << cpp::style::reversed << " Reversed " << cpp::style::reset;
    os << cpp::style::blink << " Blink " << cpp::style::reset;
    os << cpp::style::rblink << " rBlink " << cpp::style::reset;
    os << cpp::style::crossed << " Crossed " << cpp::style::reset << std::endl;

    printHeading("Background Test:");
    os << cpp::bg::green << " Green " << cpp::bg::reset;
    os << cpp::bg::red << " Red " << cpp::bg::reset;
    os << cpp::bg::black << " Black " << cpp::bg::reset;
    os << cpp::bg::yellow << " Yellow " << cpp::bg::reset;
    os << cpp::bg::blue << " Blue " << cpp::bg::reset;
    os << cpp::bg::magenta << " Magenta " << cpp::bg::reset;
    os << cpp::bg::cyan << " Cyan " << cpp::bg::reset;
    os << cpp::bg::gray << " Grey " << cpp::bg::reset << std::endl;

    printHeading("Foreground Test:");
    os << cpp::fg::green << " Green " << cpp::fg::reset;
    os << cpp::fg::red << " Red " << cpp::fg::reset;
    os << cpp::fg::black << " Black " << cpp::fg::reset;
    os << cpp::fg::yellow << " Yellow " << cpp::fg::reset;
    os << cpp::fg::blue << " Blue " << cpp::fg::reset;
    os << cpp::fg::magenta << " Magenta " << cpp::fg::reset;
    os << cpp::fg::cyan << " Cyan " << cpp::fg::reset;
    os << cpp::fg::gray << " Grey " << cpp::fg::reset << std::endl;

    printHeading("Bright Background Test:");
    os << cpp::bgB::green << " Green " << cpp::bg::reset;
    os << cpp::bgB::red << " Red " << cpp::bg::reset;
    os << cpp::bgB::black << " Black " << cpp::bg::reset;
    os << cpp::bgB::yellow << " Yellow " << cpp::bg::reset;
    os << cpp::bgB::blue << " Blue " << cpp::bg::reset;
    os << cpp::bgB::magenta << " Magenta " << cpp::bg::reset;
    os << cpp::bgB::cyan << " Cyan " << cpp::bg::reset;
    os << cpp::bgB::gray << " Grey " << cpp::bg::reset << std::endl;

    printHeading("Bright Foreground Test:");
    os << cpp::fgB::green << " Green " << cpp::fg::reset;
    os << cpp::fgB::red << " Red " << cpp::fg::reset;
    os << cpp::fgB::black << " Black " << cpp::fg::reset;
    os << cpp::fgB::yellow << " Yellow " << cpp::fg::reset;
    os << cpp::fgB::blue << " Blue " << cpp::fg::reset;
    os << cpp::fgB::magenta << " Magenta " << cpp::fg::reset;
    os << cpp::fgB::cyan << " Cyan " << cpp::fg::reset;
    os << cpp::fgB::gray << " Grey " << cpp::fg::reset << std::endl;
}

void enumerateWinTerms()
{
    std::cout << std::endl;
    std::cout << "_________________________________________________________________";
    std::cout << "\n\n"
              << cpp::style::reset << cpp::style::bold << "Printing for WinTerm = Auto" << cpp::style::reset
              << cpp::bg::reset << cpp::fg::reset << '\n';
    std::cout << "_________________________________________________________________";
    test_colors(std::cout, cpp::winTerm::Auto);
    test_colors(std::clog, cpp::winTerm::Auto);
    test_colors(std::cerr, cpp::winTerm::Auto);
    std::cout << "-------------------------------------------------------------\n\n";

    std::cout << std::endl;
    std::cout << "_________________________________________________________________";
    std::cout << "\n\n"
              << cpp::style::reset << cpp::style::bold << "Printing for WinTerm = Ansi" << cpp::style::reset
              << cpp::bg::reset << cpp::fg::reset << '\n';
    std::cout << "_________________________________________________________________";
    test_colors(std::cout, cpp::winTerm::Ansi);
    test_colors(std::clog, cpp::winTerm::Ansi);
    test_colors(std::cerr, cpp::winTerm::Ansi);
    std::cout << "-------------------------------------------------------------\n\n";

    std::cout << std::endl;
    std::cout << "_________________________________________________________________";
    std::cout << "\n\n"
              << cpp::style::reset << cpp::style::bold << "Printing for WinTerm = Native" << cpp::style::reset
              << cpp::bg::reset << cpp::fg::reset << '\n';
    std::cout << "_________________________________________________________________";
    test_colors(std::cout, cpp::winTerm::Native);
    test_colors(std::clog, cpp::winTerm::Native);
    test_colors(std::cerr, cpp::winTerm::Native);
    std::cout << "-------------------------------------------------------------\n\n";
}

void enumerateWinTermsWide()
{
    std::wcout << std::endl;
    std::wcout << "_________________________________________________________________";
    std::wcout << "\n\n"
               << cpp::style::reset << cpp::style::bold << "Printing for WinTerm = Auto" << cpp::style::reset
               << cpp::bg::reset << cpp::fg::reset << '\n';
    std::wcout << "_________________________________________________________________";
    test_colors(std::wcout, cpp::winTerm::Auto);
    test_colors(std::wclog, cpp::winTerm::Auto);
    test_colors(std::wcerr, cpp::winTerm::Auto);
    std::wcout << "-------------------------------------------------------------\n\n";

    std::wcout << std::endl;
    std::wcout << "_________________________________________________________________";
    std::wcout << "\n\n"
               << cpp::style::reset << cpp::style::bold << "Printing for WinTerm = Ansi" << cpp::style::reset
               << cpp::bg::reset << cpp::fg::reset << '\n';
    std::wcout << "_________________________________________________________________";
    test_colors(std::wcout, cpp::winTerm::Ansi);
    test_colors(std::wclog, cpp::winTerm::Ansi);
    test_colors(std::wcerr, cpp::winTerm::Ansi);
    std::wcout << "-------------------------------------------------------------\n\n";

    std::wcout << std::endl;
    std::wcout << "_________________________________________________________________";
    std::wcout << "\n\n"
               << cpp::style::reset << cpp::style::bold << "Printing for WinTerm = Native" << cpp::style::reset
               << cpp::bg::reset << cpp::fg::reset << '\n';
    std::wcout << "_________________________________________________________________";
    test_colors(std::wcout, cpp::winTerm::Native);
    test_colors(std::wclog, cpp::winTerm::Native);
    test_colors(std::wcerr, cpp::winTerm::Native);
    std::wcout << "-------------------------------------------------------------\n\n";
}

int main()
{
    std::cout << "\n\n\n"
              << cpp::style::reset << cpp::style::underline << cpp::style::bold << "Control = Auto, Wide = Off "
              << cpp::style::reset << cpp::bg::reset << cpp::fg::reset << std::endl;
    cpp::setControlMode(cpp::control::Auto);
    enumerateWinTerms();

    std::cout << "\n\n\n"
              << cpp::style::reset << cpp::style::underline << cpp::style::bold << "Control = Force, Wide = Off "
              << cpp::style::reset << cpp::bg::reset << cpp::fg::reset << std::endl;
    cpp::setControlMode(cpp::control::Force);
    enumerateWinTerms();

    std::cout << "\n\n\n"
              << cpp::style::reset << cpp::style::underline << cpp::style::bold << "Control = Off, Wide = Off "
              << cpp::style::reset << cpp::bg::reset << cpp::fg::reset << std::endl;
    cpp::setControlMode(cpp::control::Off);
    enumerateWinTerms();

    // Wide
    std::wcout << "\n\n\n"
               << cpp::style::reset << cpp::style::underline << cpp::style::bold << "Control = Auto, Wide = On "
               << cpp::style::reset << cpp::bg::reset << cpp::fg::reset << std::endl;
    cpp::setControlMode(cpp::control::Auto);
    enumerateWinTermsWide();

    std::wcout << "\n\n\n"
               << cpp::style::reset << cpp::style::underline << cpp::style::bold << "Control = Force, Wide = On "
               << cpp::style::reset << cpp::bg::reset << cpp::fg::reset << std::endl;
    cpp::setControlMode(cpp::control::Force);
    enumerateWinTermsWide();

    std::wcout << "\n\n\n"
               << cpp::style::reset << cpp::style::underline << cpp::style::bold << "Control = Off, Wide = On "
               << cpp::style::reset << cpp::bg::reset << cpp::fg::reset << std::endl;
    cpp::setControlMode(cpp::control::Off);
    enumerateWinTermsWide();
}
