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
};

#endif
