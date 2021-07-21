#ifndef GAME_HPP
#define GAME_HPP

#include "Board.hpp"

bool operator==(const Color &left, const Color &right);
bool operator!=(const Color &left, const Color &right);

class Game
{
private:
    void _LoadGraphics();
    void _LoadSounds();

public:
    Game();
    ~Game();

    bool CheckVictory() const;
    bool CheckDraw() const;

    // Runs the game loop.
    void Run();

    /* Update methods */

    void UpdateKeys();
    void UpdateBgColor();
    void Update();

    /* Draw methods */

    void DrawTopText(const std::string &text, size_t size) const;
    void DrawGameOverScreen(const std::string &text) const;
    void Draw() const;

private:
    int m_player;
    bool m_gameBegan, m_darkMode;
    Color m_bgColor;
    std::string m_text;

    std::map<std::string, Texture2D> m_textures;
    std::map<std::string, Sound> m_sounds;

    std::unique_ptr<Board> m_board;
};

#endif
