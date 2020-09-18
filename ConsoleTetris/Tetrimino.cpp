#include "pch.h"
#include "Tetrimino.h"

void Tetrimino::SetPosition(const COORD newPos)
{
    for (int i = 0; i < 4; ++i)
    {
        _layout[i].X += newPos.X - _pos.X;
        _layout[i].Y += newPos.Y - _pos.Y;
    }
    _pos = newPos;
}

void ShapeL::SetRotation(const unsigned short newRot)
{
    Tetrimino::SetRotation(newRot);
    if (newRot == 0)
    {
        _layout[0] = {0, 1};
        _layout[1] = {1, 1};
        _layout[2] = {2, 1};
        _layout[3] = {2, 0};
    }
    else if (newRot == 1)
    {
        _layout[0] = {0, 0};
        _layout[1] = {0, 1};
        _layout[2] = {0, 2};
        _layout[3] = {1, 2};
    }
    else if (newRot == 2)
    {
        _layout[0] = {2, 0};
        _layout[1] = {1, 0};
        _layout[2] = {0, 0};
        _layout[3] = {0, 1};
    }
    else if (newRot == 3)
    {
        _layout[0] = {1, 2};
        _layout[1] = {1, 1};
        _layout[2] = {1, 0};
        _layout[3] = {0, 0};
    }
    for (int i = 0; i < 4; ++i)
    {
        _layout[i].X += _pos.X;
        _layout[i].Y += _pos.Y;
    }
}

void ShapeL2::SetRotation(const unsigned short newRot)
{
    Tetrimino::SetRotation(newRot);
    if (newRot == 0)
    {
        _layout[0] = {2, 1};
        _layout[1] = {1, 1};
        _layout[2] = {0, 1};
        _layout[3] = {0, 0};
    }
    else if (newRot == 1)
    {
        _layout[0] = {0, 2};
        _layout[1] = {0, 1};
        _layout[2] = {0, 0};
        _layout[3] = {1, 0};
    }
    else if (newRot == 2)
    {
        _layout[0] = {0, 0};
        _layout[1] = {1, 0};
        _layout[2] = {2, 0};
        _layout[3] = {2, 1};
    }
    else if (newRot == 3)
    {
        _layout[0] = {1, 0};
        _layout[1] = {1, 1};
        _layout[2] = {1, 2};
        _layout[3] = {0, 2};
    }
    for (int i = 0; i < 4; ++i)
    {
        _layout[i].X += _pos.X;
        _layout[i].Y += _pos.Y;
    }
}

void ShapeBar::SetRotation(const unsigned short newRot)
{
    Tetrimino::SetRotation(newRot);
    if (newRot == 0 || newRot == 2)
    {
        _layout[0] = {0, 0};
        _layout[1] = {1, 0};
        _layout[2] = {2, 0};
        _layout[3] = {3, 0};
    }
    else if (newRot == 1 || newRot == 3)
    {
        _layout[0] = {0, 0};
        _layout[1] = {0, 1};
        _layout[2] = {0, 2};
        _layout[3] = {0, 3};
    }
    for (int i = 0; i < 4; ++i)
    {
        _layout[i].X += _pos.X;
        _layout[i].Y += _pos.Y;
    }
}

void ShapeBlock::SetRotation(const unsigned short newRot)
{
    Tetrimino::SetRotation(newRot);
    _layout[0] = {0, 0};
    _layout[1] = {1, 0};
    _layout[2] = {1, 1};
    _layout[3] = {0, 1};
    for (int i = 0; i < 4; ++i)
    {
        _layout[i].X += _pos.X;
        _layout[i].Y += _pos.Y;
    }
}

void ShapeS::SetRotation(const unsigned short newRot)
{
    Tetrimino::SetRotation(newRot);
    if (newRot == 0 || newRot == 2)
    {
        _layout[0] = {0, 1};
        _layout[1] = {1, 1};
        _layout[2] = {1, 0};
        _layout[3] = {2, 0};
    }
    else if (newRot == 1 || newRot == 3)
    {
        _layout[0] = {0, 0};
        _layout[1] = {0, 1};
        _layout[2] = {1, 1};
        _layout[3] = {1, 2};
    }
    for (int i = 0; i < 4; ++i)
    {
        _layout[i].X += _pos.X;
        _layout[i].Y += _pos.Y;
    }
}

void ShapeS2::SetRotation(const unsigned short newRot)
{
    Tetrimino::SetRotation(newRot);
    if (newRot == 0 || newRot == 2)
    {
        _layout[0] = {0, 0};
        _layout[1] = {1, 0};
        _layout[2] = {1, 1};
        _layout[3] = {2, 1};
    }
    else if (newRot == 1 || newRot == 3)
    {
        _layout[0] = {1, 0};
        _layout[1] = {1, 1};
        _layout[2] = {0, 1};
        _layout[3] = {0, 2};
    }
    for (int i = 0; i < 4; ++i)
    {
        _layout[i].X += _pos.X;
        _layout[i].Y += _pos.Y;
    }
}

void ShapeT::SetRotation(const unsigned short newRot)
{
    Tetrimino::SetRotation(newRot);
    if (newRot == 0)
    {
        _layout[0] = {1, 0};
        _layout[1] = {0, 1};
        _layout[2] = {1, 1};
        _layout[3] = {2, 1};
    }
    else if (newRot == 1)
    {
        _layout[0] = {1, 1};
        _layout[1] = {0, 0};
        _layout[2] = {0, 1};
        _layout[3] = {0, 2};
    }
    else if (newRot == 2)
    {
        _layout[0] = {1, 1};
        _layout[1] = {0, 0};
        _layout[2] = {1, 0};
        _layout[3] = {2, 0};
    }
    else if (newRot == 3)
    {
        _layout[0] = {0, 1};
        _layout[1] = {1, 0};
        _layout[2] = {1, 1};
        _layout[3] = {1, 2};
    }
    for (int i = 0; i < 4; ++i)
    {
        _layout[i].X += _pos.X;
        _layout[i].Y += _pos.Y;
    }
}
