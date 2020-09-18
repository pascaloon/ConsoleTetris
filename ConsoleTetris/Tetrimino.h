#pragma once

class Tetrimino
{
public:
    virtual const std::vector<COORD>& GetAbsoluteBlocks() const { return _layout; }
    
    void SetPosition(const COORD newPos);
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
    virtual void SetRotation(const unsigned short newRot) override;
};

class ShapeL2 : public Tetrimino
{
public:
    virtual ~ShapeL2() = default;
    ShapeL2() { _layout.resize(4); }
    virtual void SetRotation(const unsigned short newRot) override;
};

class ShapeBar : public Tetrimino
{
public:
    virtual ~ShapeBar() = default;
    ShapeBar() { _layout.resize(4); }
    virtual void SetRotation(const unsigned short newRot) override;
};

class ShapeBlock : public Tetrimino
{
public:
    virtual ~ShapeBlock() = default;
    ShapeBlock() { _layout.resize(4); }
    virtual void SetRotation(const unsigned short newRot) override;
};

class ShapeS : public Tetrimino
{
public:
    virtual ~ShapeS() = default;
    ShapeS() { _layout.resize(4); }
    virtual void SetRotation(const unsigned short newRot) override;
};

class ShapeS2 : public Tetrimino
{
public:
    virtual ~ShapeS2() = default;
    ShapeS2() { _layout.resize(4); }
    virtual void SetRotation(const unsigned short newRot) override;
};

class ShapeT : public Tetrimino
{
public:
    virtual ~ShapeT() = default;
    ShapeT() { _layout.resize(4); }
    virtual void SetRotation(const unsigned short newRot) override;
};


