#include "View.h"

void View::printSeparatingLine()
{
    std::cout << "--------------------------------\n";
}

void View::printUserInputRequest()
{
    std::cout << "user input (q - quit): ";
}

void View::printUserRequest(const std::string& request)
{
    std::cout << request;
}

void View::clearScreen()
{
    COORD topLeft = { 0, 0 };
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen;
    DWORD written;

    GetConsoleScreenBufferInfo(console, &screen);
    FillConsoleOutputCharacterA(
        console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
    );
    FillConsoleOutputAttribute(
        console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
        screen.dwSize.X * screen.dwSize.Y, topLeft, &written
    );
    SetConsoleCursorPosition(console, topLeft);
}

void View::showMainMenu()
{
    clearScreen();
    for (int i = 0; i < this->main_menu_strings_.size(); i++)
        std::cout << i + 1 << this->main_menu_strings_[i] << "\n";
    printSeparatingLine();
}

void View::showPossibleInstruments()
{
    clearScreen();
    std::cout << "Instrment type in database:\n";
    for (int i = 0; i < this->possible_instruments.size(); i++)
        std::cout << i + 1 << this->possible_instruments[i] << '\n';
    printSeparatingLine();
}
