#ifndef GAME_HPP
#define GAME_HPP

#include <array>
#include <iostream>
#include <string>
#include "Line.hpp"

enum class BoxStates { NONE, CROSS, CIRCLE };

bool operator==(const Color &left, const Color &right);
bool operator!=(const Color &left, const Color &right);

class Game
{
private:
    void _InitArrays();
    void _LoadGraphics();
    void _LoadSounds();

public:
    Game();
    ~Game();

    bool CheckRows();
    bool CheckColumns();
    bool CheckDiagonals();

    bool CheckVictory();
    bool CheckDraw();

    // Runs the game loop.
    void Run();

    void Update();

    /* Draw methods */

    void DrawBoard();
    void DrawTopText(const std::string &text, const size_t size);
    void DrawGameOverScreen(const std::string &text);
    void Draw();

private:
    int m_player;
    bool m_gameBegan, m_darkMode;
    Color m_bgColor;
    std::string m_text;

    std::array<std::array<Rectangle, 3>, 3> m_grid;
    std::array<std::array<BoxStates, 3>, 3> m_board;

    Image m_imgIcon;
    Texture2D m_texCross, m_texCircle;
    Sound m_player1Sound, m_player2Sound;

    Line m_line;
};

#endif
