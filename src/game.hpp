#ifndef GAME_HPP
#define GAME_HPP

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

    bool CheckRows() const;
    bool CheckColumns() const;
    bool CheckDiagonals() const;

    bool CheckVictory() const;
    bool CheckDraw() const;

    // Runs the game loop.
    void Run();

    void Update();

    /* Draw methods */

    void DrawBoard() const;
    void DrawTopText(const std::string &text, size_t size) const;
    void DrawGameOverScreen(const std::string &text) const;
    void Draw() const;

private:
    int m_player;
    bool m_gameBegan, m_darkMode;
    Color m_bgColor;
    std::string m_text;

    std::array<std::array<std::pair<BoxStates, Rectangle>, 3>, 3> m_boxes;

    Image m_imgIcon;

    std::map<std::string, Texture2D> m_textures;
    std::map<std::string, Sound> m_sounds;

    mutable Line m_line;
};

#endif
