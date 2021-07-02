#ifndef GAME_HPP
#define GAME_HPP

#include "check.hpp"
#include "draw.hpp"

enum class A;

class Game
{
private:
    void _InitArrays();
    void _LoadGraphics();
    void _LoadSounds();

public:
    Game();
    ~Game();

    void Run();
    void Update();
    void Draw();

private:
    int m_player;
    bool m_gameBegan, m_darkMode;
    Color m_bgColor;
    std::string m_text;

    std::array<std::array<Rectangle, 3>, 3> m_grid;
    std::array<std::array<BoxStates, 3>, 3> m_board;

    Image m_imgIcon;
    Texture2D m_texBoard, m_texCross, m_texCircle;
    Sound m_player1Sound, m_player2Sound;
};

#endif
