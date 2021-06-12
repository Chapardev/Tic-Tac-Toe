#ifndef GAME_HPP
#define GAME_HPP

#include "check.hpp"
#include "draw.hpp"

class Game
{
public:
    Game();
    ~Game();

    void Run();
    void Update();
    void Draw();

private:
    // Constants
    static const int c_side = 3;

    const int c_screenWidth = 600;
    const int c_screenHeight = 700;
    const int c_fps = 60;
    
    const int c_lineThickness = 5;

    const int c_boxWidth = (c_screenWidth - c_lineThickness) / c_side;
    const int c_boxHeight = (c_screenWidth - c_lineThickness) / c_side;

    const char c_none = ' ', c_cross = 'X', c_circle = 'O';
    const std::array<char, c_side> c_states = {c_none, c_cross, c_circle};

    // Attributes
    int m_player;
    bool m_gameBegan, m_darkMode;
    Color m_bgColor;
    std::string m_text;

    std::array<std::array<Rectangle, c_side>, c_side> m_grid;
    std::array<std::array<char, c_side>, c_side> m_board;

    Image m_imgIcon;
    Texture2D m_texBoard, m_texCross, m_texCircle;
};

#endif
