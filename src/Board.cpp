#include "Board.hpp"

Board::Board(float lineThickness)
    : m_lineThickness{lineThickness}
{
    const float boxWidth{(GetScreenWidth() - m_lineThickness) / 3.f};
    const float boxHeight{(GetScreenWidth() - m_lineThickness) / 3.f};

    int x{0};
    for (auto &subArray : m_boxes)
    {
        int y{0};
        for (auto &box : subArray)
        {
            box.first = BoxStates::NONE;
            box.second = {
                (boxWidth + m_lineThickness) * static_cast<float>(x),
                static_cast<float>((GetScreenHeight() - GetScreenWidth()) + (boxHeight + m_lineThickness) * y),
                boxWidth, boxHeight
            };
            y++;
        }
        x++;
    }
}

bool Board::CheckRows(int playerTurn) const
{
    const BoxStates playerState{static_cast<BoxStates>(playerTurn)};
    for (size_t i{0}; i < m_boxes.size(); i++)
    {
        if (std::all_of(m_boxes.begin(), m_boxes.end(), [=](auto subArray){ return subArray[i].first == playerState; }))
        {
            const Vector2 startPos = {
                m_boxes[0][i].second.x + m_boxes[0][i].second.width / 4.f,
                m_boxes[0][i].second.y + m_boxes[0][i].second.height / 2.f - m_lineThickness
            }; 
            const Vector2 endPos = {
                m_boxes[m_boxes.size()-1][i].second.x + m_boxes[m_boxes.size()-1][i].second.width * 0.75f,
                m_boxes[m_boxes.size()-1][i].second.y + m_boxes[m_boxes.size()-1][i].second.height / 2.f - m_lineThickness
            };

            m_line = Line(startPos, endPos, m_lineThickness);

            return true;
        }
    }

    return false;
}

bool Board::CheckColumns(int playerTurn) const
{
    const BoxStates playerState{static_cast<BoxStates>(playerTurn)};
    for (const auto &subArray : m_boxes)
    {
        if (std::all_of(subArray.begin(), subArray.end(), [=](auto pair){ return pair.first == playerState; }))
        {
            const Vector2 startPos{
                subArray[0].second.x + subArray[0].second.width / 2.f - m_lineThickness, 
                subArray[0].second.y + subArray[0].second.height / 4.f
            };
            const Vector2 endPos{
                subArray[m_boxes.size()-1].second.x + subArray[m_boxes.size()-1].second.width / 2.f - m_lineThickness,
                subArray[m_boxes.size()-1].second.y + subArray[m_boxes.size()-1].second.height * 0.75f
            };

            m_line = Line(startPos, endPos, m_lineThickness);
            return true;
        }
    }

    return false;
}

bool Board::CheckDiagonals(int playerTurn) const
{
    const BoxStates playerState{static_cast<BoxStates>(playerTurn)};
    bool result{true};

    for (size_t i{0}; i < m_boxes.size(); i++)
    {
        if (m_boxes[i][i].first != playerState)
        {
            result = false;
        }
    }

    if (result) 
    {
        const Rectangle firstRec = m_boxes[0][0].second;
        const Vector2 startPos{
            firstRec.x + firstRec.width / 2.f - m_lineThickness * 3, 
            firstRec.y + firstRec.height / 2.f - m_lineThickness * 3
        };

        const Rectangle lastRec = m_boxes[m_boxes.size()-1][m_boxes.size()-1].second;
        const Vector2 endPos{
            lastRec.x + lastRec.width / 2.f,
            lastRec.y + lastRec.height / 2.f
        };

        m_line = Line(startPos, endPos, m_lineThickness);

        return result;
    }
    
    result = true;
    for (size_t i{0}; i < m_boxes.size(); i++)
    {
        if (m_boxes[m_boxes.size() - i - 1][i].first != playerState)
        {
            result = false;
        }
    }

    if (result)
    {
        const size_t last{m_boxes.size()-1};
        const Vector2 startPos{
            m_boxes[0][last].second.x + m_boxes[0][last].second.width / 2.f - m_lineThickness * 4.3f,
            m_boxes[0][last].second.y + m_boxes[0][last].second.height / 2.f + m_lineThickness * 1.4f
        };
        const Vector2 endPos{
            m_boxes[last][0].second.x + m_boxes[last][0].second.width / 2.f + m_lineThickness * 1.4f,
            m_boxes[last][0].second.y + m_boxes[last][0].second.height / 2.f - m_lineThickness * 4.3f
        };

        m_line = Line(startPos, endPos, m_lineThickness);
    }

    return result;
}

void Board::Draw(const std::map<std::string, Texture2D> &textures) const
{
    for (const auto &subArray : m_boxes)
    {
        for (const auto &box : subArray)
        {
            DrawRectangleRec(box.second, BLUE);

            if (box.first == BoxStates::CROSS)
            {
                DrawTexture(textures.at("cross"), box.second.x + m_lineThickness, box.second.y + m_lineThickness, WHITE);
            }
            else if (box.first == BoxStates::CIRCLE)
            {
                DrawTexture(textures.at("circle"), box.second.x + m_lineThickness, box.second.y + m_lineThickness, WHITE);
            }
        }
    }
}

void Board::DrawLine(const Color &color) const
{
    m_line.Draw(color);
}
