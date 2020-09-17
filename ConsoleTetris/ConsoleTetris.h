#pragma once
#include "pch.h"

enum class GameState
{
    Waiting,
    Running,
    GameOver,
};


class ConsoleTetris
{
public:
    ConsoleTetris(const unsigned int width, const unsigned int height)
        : _width(width)
        , _height(height)
    {}

    void Init();
    
    // Runs the game loop
    void Run();

    // One game loop iteration
    void Tick();

    // Draw once per loop iteration
    void Draw();

    void Clear();

private:
    const unsigned int _width, _height;
    bool _quit = false;

    HANDLE _hConsole;
    CONSOLE_SCREEN_BUFFER_INFO _initConsoleInfo;
    COORD _origin;
};
