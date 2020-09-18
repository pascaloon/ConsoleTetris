#include "pch.h"
#include "ConsoleTetris.h"

#include <iostream>
#include <stdbool.h>
#include <stdbool.h>
#include <stdbool.h>
#include <stdbool.h>
#include <stdbool.h>
#include <stdbool.h>
#include <thread>

void ConsoleTetris::Init()
{
    _hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    _hConsoleInput = GetStdHandle(STD_INPUT_HANDLE);

    // Useless
    DWORD written, reserved, clearCount;

    // Make room for game (+ 2 borders)
    const unsigned int totalHeight = _height + 2;
    const unsigned int totalWidth = _width + 2;

    std::vector<char> lines = std::vector<char>(totalHeight, '\n');
    WriteConsoleA(_hConsole, &lines[0], totalHeight, &written, &reserved);

    // Get current console info and change origin to top left corner 
    GetConsoleScreenBufferInfo(_hConsole, &_initConsoleInfo);
    _origin = {1, _initConsoleInfo.dwCursorPosition.Y - static_cast<SHORT>(totalHeight) + 1};
    
    SHORT y = _origin.Y - 1;
    for (unsigned int i = 0; i < totalHeight; ++i)
    {
        FillConsoleOutputCharacterA(_hConsole, 'x', totalWidth, {0, y}, &clearCount);
        ++y;
    }
    
    y = _origin.Y;
    for (unsigned int i = 0; i < _height; ++i)
    {
        FillConsoleOutputCharacterA(_hConsole, ' ', _width, {1, y}, &clearCount);
        ++y;
    }

    // Init map memory
    _map.resize(_height);
    for (unsigned int i = 0; i < _height; ++i)
        _map[i].resize(_width, false);

    SpawnTetrimino();
}

void ConsoleTetris::Run()
{
    constexpr unsigned int SLEEP_TIME_MS = 50;
    constexpr unsigned int FALL_TIME_MS = 500;
    
    while (!_quit)
    {
        _fallCounter += SLEEP_TIME_MS;
        const bool fall = _fallCounter == FALL_TIME_MS;
        if (fall)
            _fallCounter = 0;
        
        Tick(fall);
        Draw();

        std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_TIME_MS));
    }
}

void ConsoleTetris::Tick(const bool fall)
{
    COORD deltaMove{0,0};
    int deltaRot = 0;
    bool fastFall = false;
    // Let's read keys:
    DWORD eventsCountRead = 0;
    GetNumberOfConsoleInputEvents(_hConsoleInput, &eventsCountRead);
    if (eventsCountRead > 0)
    {
        std::vector<INPUT_RECORD> records(eventsCountRead);
        ReadConsoleInputA(_hConsoleInput, &records[0], (DWORD)records.size(), &eventsCountRead);
        for (const INPUT_RECORD& record : records)
        {
            if (record.EventType != KEY_EVENT || !record.Event.KeyEvent.bKeyDown)
                continue;
            switch (record.Event.KeyEvent.uChar.AsciiChar)
            {
                case 'a':
                    deltaMove.X -= 1;
                    break;
                case 'd':
                    deltaMove.X += 1;
                    break;
                case 'w':
                    deltaRot += 1;
                    break;
                case 's':
                    fastFall = true;
                    break;
                default:
                    break;
            }
        }
    }

    if (fastFall)
    {
        COORD pos = _currentPiece->GetPosition();
        while (ValidateTetrimino(*_currentPiece))
        {
            pos.Y += 1;
            _currentPiece->SetPosition(pos);
        }
        pos.Y -= 1;
        _currentPiece->SetPosition(pos);
        LockCurrentPiece();
    }
    else
    {
        // Rotate
        int rot = _currentPiece->GetRotation();
        if (deltaRot > 0)
            _currentPiece->SetRotation((rot + deltaRot) % 4);

        // Move
        COORD pos = _currentPiece->GetPosition();
        _currentPiece->SetPosition({pos.X + deltaMove.X, pos.Y + deltaMove.Y});

        // Validate
        if (!ValidateTetrimino(*_currentPiece.get()))
        {
            if (deltaRot > 0)
                _currentPiece->SetRotation(rot);
            _currentPiece->SetPosition(pos);
        }

        if (fall)
        {
            pos = _currentPiece->GetPosition();
            _currentPiece->SetPosition({pos.X, pos.Y + 1});
            if (!ValidateTetrimino(*_currentPiece))
            {
                _currentPiece->SetPosition(pos);
                LockCurrentPiece();
            }
        }

        // Fall preview
        pos = _currentPiece->GetPosition();
        _fallPreview->SetRotation(_currentPiece->GetRotation());
        _fallPreview->SetPosition(pos);
        while (ValidateTetrimino(*_fallPreview))
        {
            pos.Y += 1;
            _fallPreview->SetPosition(pos);
        }
        pos.Y -= 1;
        _fallPreview->SetPosition(pos);
    }
    
}

bool ConsoleTetris::ValidateTetrimino(const Tetrimino& tetrimino)
{
    const std::vector<COORD>& blocks = tetrimino.GetAbsoluteBlocks();

    bool invalidMove = false;
    for (COORD c: blocks)
    {
        invalidMove = c.X < 0 || c.X >= _width || c.Y < 0 || c.Y >= _height || _map[c.Y][c.X];
        if (invalidMove)
            break;
    }

    return !invalidMove;
}

void ConsoleTetris::LockCurrentPiece()
{
    const std::vector<COORD>& blocks = _currentPiece->GetAbsoluteBlocks();

    for (COORD c: blocks)
    {
        _map[c.Y][c.X] = true;
    }

    // Validate Map for lines
    _refreshMap = true;
    for (int y = 0; y < _height; ++y)
    {
        bool fullLine = true;
        for (int x = 0; x < _width; ++x)
        {
            fullLine = fullLine && _map[y][x];
        }
        if (fullLine)
        {
            // cascade
            for (int ly = y; ly > 0; --ly)
            {
                for (int x = 0; x < _width; ++x)
                {
                    _map[ly][x] = _map[ly-1][x];
                }       
            }
        }
    }

    _oldPiecePos.clear();
    _currentPiece.reset();
    _fallPreview.reset();
    SpawnTetrimino();
    if (!ValidateTetrimino(*_currentPiece))
    {
        std::cout << std::endl << "Game Over!" << std::endl;
        _quit = true;
    }
}

void ConsoleTetris::SpawnTetrimino()
{
    int r = rand() % 7;
    switch (r)
    {
        case 0:
            _currentPiece = std::make_unique<ShapeL>();
            _fallPreview = std::make_unique<ShapeL>();
            break;
        case 1:
            _currentPiece = std::make_unique<ShapeL2>();
            _fallPreview = std::make_unique<ShapeL2>();
            break;
        case 2:
            _currentPiece = std::make_unique<ShapeBar>();
            _fallPreview = std::make_unique<ShapeBar>();
            break;
        case 3:
            _currentPiece = std::make_unique<ShapeBlock>();
            _fallPreview = std::make_unique<ShapeBlock>();
            break;
        case 4:
            _currentPiece = std::make_unique<ShapeS>();
            _fallPreview = std::make_unique<ShapeS>();
            break;
        case 5:
            _currentPiece = std::make_unique<ShapeS2>();
            _fallPreview = std::make_unique<ShapeS2>();
            break;
        case 6:
            _currentPiece = std::make_unique<ShapeT>();
            _fallPreview = std::make_unique<ShapeT>();
            break;
    }

    _currentPiece->SetRotation(0);
    _currentPiece->SetPosition({0, 0});
    _fallPreview->SetRotation(0);
    _fallPreview->SetPosition({0, 0});
}


void ConsoleTetris::Draw()
{
    // https://docs.microsoft.com/en-us/windows/console/console-functions
    DWORD clearCount;

    if (_refreshMap)
    {
        for (SHORT y = 0; y < _height; ++y)
            {
                for (SHORT x = 0; x < _width; ++x)
                {
                    FillConsoleOutputAttribute(_hConsole, _initConsoleInfo.wAttributes, 1, {_origin.X + x, _origin.Y + y}, &clearCount);
                    if (_map[y][x])
                        FillConsoleOutputCharacterA(_hConsole, 'x', 1, {_origin.X + x, _origin.Y + y}, &clearCount);
                    else
                        FillConsoleOutputCharacterA(_hConsole, ' ', 1, {_origin.X + x, _origin.Y + y}, &clearCount);
                }
            }
    }
    
    
    // Clear old piece pos
    for (COORD c : _oldPiecePos)
    {
        FillConsoleOutputCharacterA(_hConsole, ' ', 1, {_origin.X + c.X, _origin.Y + c.Y}, &clearCount);        
    }

    const std::vector<COORD>& previewBlocks = _fallPreview->GetAbsoluteBlocks();
    for (COORD c : previewBlocks)
    {
        FillConsoleOutputAttribute(_hConsole, FOREGROUND_GREEN, 1, {_origin.X + c.X, _origin.Y + c.Y}, &clearCount);
        FillConsoleOutputCharacterA(_hConsole, 'x', 1, {_origin.X + c.X, _origin.Y + c.Y}, &clearCount);                
    }

    // Draw current piece pos
    const std::vector<COORD>& blocks = _currentPiece->GetAbsoluteBlocks();
    for (COORD c : blocks)
    {
        FillConsoleOutputAttribute(_hConsole, FOREGROUND_BLUE, 1, {_origin.X + c.X, _origin.Y + c.Y}, &clearCount);
        FillConsoleOutputCharacterA(_hConsole, 'x', 1, {_origin.X + c.X, _origin.Y + c.Y}, &clearCount);                
    }

    _oldPiecePos = blocks;
    _oldPiecePos.insert(_oldPiecePos.end(), previewBlocks.begin(), previewBlocks.end());
    
    
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
