#ifndef GAME_HPP
#define GAME_HPP

#include "check.hpp"
#include "draw.hpp"

enum class A;

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
    const char c_none = ' ', c_cross = 'X', c_circle = 'O';
    const std::array<char, 3> c_states = {c_none, c_cross, c_circle};

    // Attributes
    int m_player;
    bool m_gameBegan, m_darkMode;
    Color m_bgColor;
    std::string m_text;

    std::array<std::array<Rectangle, 3>, 3> m_grid;
    std::array<std::array<char, 3>, 3> m_board;

    Image m_imgIcon;
    Texture2D m_texBoard, m_texCross, m_texCircle;
    Sound m_player1Sound, m_player2Sound;
};

#endif
