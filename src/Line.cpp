#include "Line.hpp"

Line::Line(const Vector2 &startPos, const Vector2 &endPos, float thickness)
    : m_startPos{startPos}, m_endPos{endPos}, m_thickness{thickness}
{
    
}

void Line::Draw(const Color &color) const
{
    DrawLineEx(m_startPos, m_endPos, m_thickness, color);
}
