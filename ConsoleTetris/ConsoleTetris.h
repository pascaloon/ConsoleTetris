#pragma once
#include "pch.h"

#include <stdbool.h>

#include "TypeDefs.h"
#include "Tetrimino.h"

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
    void Tick(const bool fall);

    // Draw once per loop iteration
    void Draw();

    void Clear();

private:
    bool ValidateTetrimino(const Tetrimino& tetrimino);
    void LockCurrentPiece();
    void SpawnTetrimino();
    
    const unsigned int _width, _height;
    bool _quit = false;

    HANDLE _hConsole;
    HANDLE _hConsoleInput;
    CONSOLE_SCREEN_BUFFER_INFO _initConsoleInfo;
    COORD _origin;

    Map _map;

    std::unique_ptr<Tetrimino> _currentPiece;
    std::unique_ptr<Tetrimino> _fallPreview;
    std::vector<COORD> _oldPiecePos;

    bool _refreshMap = false;
    unsigned int _fallCounter = 0;
};
