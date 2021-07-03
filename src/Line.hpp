#ifndef LINE_HPP
#define LINE_HPP

#include "raylib.h"

class Line
{
public:
    Line(const Vector2 &startPos={0, 0}, const Vector2 &endPos={0, 0}, float thickness=0.f);

    void Draw(const Color &color);

private:
    Vector2 m_startPos;
    Vector2 m_endPos;
    float m_thickness;
};

#endif
