#include "pch.h"
#include "ConsoleTetris.h"

#include <iostream>
#include <thread>

void ConsoleTetris::Init()
{
    _hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Useless
    DWORD written, reserved, clearCount;

    // Make room for game (+ 2 borders)
    const unsigned int totalHeight = _height + 2;
    const unsigned int totalWidth = _width + 2;
    
    std::unique_ptr<char[]> lines = std::unique_ptr<char[]>(new char[totalHeight]);
    for (unsigned int i = 0; i < totalHeight; ++i)
        lines[i] = '\n';
    WriteConsoleA(_hConsole, lines.get(), totalHeight, &written, &reserved);

    // Get current console info and change origin to top left corner 
    GetConsoleScreenBufferInfo(_hConsole, &_initConsoleInfo);
    _origin = {0, _initConsoleInfo.dwCursorPosition.Y - static_cast<SHORT>(totalHeight)};
    
    SHORT y = _origin.Y;
    for (unsigned int i = 0; i < totalHeight; ++i)
    {
        FillConsoleOutputCharacterA(_hConsole, 'x', totalWidth, {0, y}, &clearCount);
        ++y;
    }
    
    y = _origin.Y + 1;
    for (unsigned int i = 0; i < _height; ++i)
    {
        FillConsoleOutputCharacterA(_hConsole, ' ', _width, {1, y}, &clearCount);
        ++y;
    }

}

void ConsoleTetris::Run()
{
    while (!_quit)
    {
        Tick();
        Draw();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

void ConsoleTetris::Tick()
{
    // std::cout << "Hello" << std::endl;
}

void ConsoleTetris::Draw()
{
    // https://docs.microsoft.com/en-us/windows/console/console-functions
    
    // DWORD clearCount;
    //
    // ResizePseudoConsole(_hConsole, {5, 5});
    //
    // FillConsoleOutputCharacterA(_hConsole, 'z', csbi.dwSize.X*3, csbi.dwCursorPosition, &clearCount);
    //
    //
    // COORD coord = csbi.dwCursorPosition;
    // for (int i = 0; i < 5; ++i)
    // {
    //     FillConsoleOutputCharacterA(_hConsole, 'x', 5, coord, &clearCount);
    //     ++coord.Y;
    // }
}
