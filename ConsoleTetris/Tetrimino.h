#pragma once

class Tetrimino
{
public:
    virtual const std::vector<COORD>& GetAbsoluteBlocks() const { return _layout; }
    
    virtual void SetPosition(const COORD newPos) { _pos = newPos; }
    COORD GetPosition() const { return _pos; }
    
    virtual void SetRotation(const unsigned short newRot) { _rot = newRot; }
    unsigned short GetRotation() const { return _rot; }

    virtual ~Tetrimino() = default;

protected:
    std::vector<COORD> _layout;
    unsigned short _rot = 0;
    COORD _pos{0, 0};
};


class ShapeL : public Tetrimino
{
public:
    virtual ~ShapeL() = default;
    ShapeL() { _layout.resize(4); }

    virtual void SetPosition(const COORD newPos) override
    {
        // Set to new pos
        for (int i = 0; i < 4; ++i)
        {
            _layout[i].X += newPos.X - _pos.X;
            _layout[i].Y += newPos.Y - _pos.Y;
        }

        Tetrimino::SetPosition(newPos);

    }

    virtual void SetRotation(const unsigned short newRot) override
    {
        Tetrimino::SetRotation(newRot);
        if (newRot == 0)
        {
            _layout[0] = {0, 1};
            _layout[1] = {1, 1};
            _layout[2] = {2, 1};
            _layout[3] = {2, 0};
        } else if (newRot == 1) {
            _layout[0] = {0, 0};
            _layout[1] = {0, 1};
            _layout[2] = {0, 2};
            _layout[3] = {1, 2};
        } else if (newRot == 2) {
            _layout[0] = {2, 0};
            _layout[1] = {1, 0};
            _layout[2] = {0, 0};
            _layout[3] = {0, 1};
        } else if (newRot == 3) {
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
    
};
