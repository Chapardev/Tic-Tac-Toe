#include "Game.hpp"

bool operator==(const Color &left, const Color &right)
{
    return (left.r == right.r) && (left.g == right.g) && (left.b == right.b);
}

bool operator!=(const Color &left, const Color &right)
{
    return !(left == right);
}

void Game::_InitArrays()
{
    const int lineThickness{5};
    const int boxWidth{(GetScreenWidth() - lineThickness) / 3};
    const int boxHeight{(GetScreenWidth() - lineThickness) / 3};

    int x{0};
    for (auto &subArray : m_boxes)
    {
        int y{0};
        for (auto &box : subArray)
        {
            box.first = BoxStates::NONE;
            box.second = {
                static_cast<float>((boxWidth + lineThickness) * x),
                static_cast<float>((GetScreenHeight() - GetScreenWidth()) + (boxHeight + lineThickness) * y),
                static_cast<float>(boxWidth), static_cast<float>(boxHeight)
            };
            
            y++;
        }
        x++;
    }
}

void Game::_LoadGraphics()
{
    m_imgIcon = LoadImage("../assets/cross.png");
    SetWindowIcon(m_imgIcon);
    UnloadImage(m_imgIcon);

    m_textures["cross"] = LoadTexture("../assets/cross.png");
    m_textures["circle"] = LoadTexture("../assets/circle.png");
}

void Game::_LoadSounds()
{
    m_sounds["player1"] = LoadSound("../assets/player1.wav");
    m_sounds["player2"] = LoadSound("../assets/player2.wav");
}

Game::Game() 
    : m_player{1}, m_gameBegan{false}, m_darkMode{false}, m_bgColor{WHITE}
{
    InitWindow(600, 700, "Tic Tac Toe");
    InitAudioDevice();

    this->_InitArrays();
    this->_LoadGraphics();
    this->_LoadSounds();

    SetTargetFPS(60);
}

Game::~Game()
{
    for (const auto &sound : m_sounds)
    {
        UnloadSound(sound.second);
    }

    for (const auto &texture : m_textures)
    {
        UnloadTexture(texture.second);
    }

    CloseAudioDevice();
    CloseWindow();
}

bool Game::CheckRows() const
{
    const BoxStates playerState{static_cast<BoxStates>(m_player)};

    for (size_t i{0}; i < m_boxes.size(); i++)
    {
        // if (m_boxes[0][i].first == playerState && m_boxes[1][i].first == playerState && m_boxes[2][i].first == playerState)
        if (std::all_of(m_boxes.begin(), m_boxes.end(), [=](auto subArray){ return subArray[i].first == playerState; }))
        {
            const float thickness = 5.f;

            const Vector2 startPos = {
                m_boxes[0][i].second.x + m_boxes[0][i].second.width / 4.f,
                m_boxes[0][i].second.y + m_boxes[0][i].second.height / 2.f - thickness
            };
            
            const Vector2 endPos = {
                m_boxes[m_boxes.size()-1][i].second.x + m_boxes[m_boxes.size()-1][i].second.width * 0.75f,
                m_boxes[m_boxes.size()-1][i].second.y + m_boxes[m_boxes.size()-1][i].second.height / 2.f - thickness
            };

            m_line = Line(startPos, endPos, thickness);

            return true;
        }
    }

    return false;
}

bool Game::CheckColumns() const
{
    const BoxStates playerState{static_cast<BoxStates>(m_player)};
    for (const auto &subArray : m_boxes)
    {
        if (std::all_of(subArray.begin(), subArray.end(), [=](auto pair){ return pair.first == playerState; }))
        {
            const float thickness{5.f};

            const Vector2 startPos = {
                subArray[0].second.x + subArray[0].second.width / 2.f - thickness, 
                subArray[0].second.y + subArray[0].second.height / 4.f
            };
            
            const Vector2 endPos = {
                subArray[m_boxes.size()-1].second.x + subArray[m_boxes.size()-1].second.width / 2.f - thickness,
                subArray[m_boxes.size()-1].second.y + subArray[m_boxes.size()-1].second.height * 0.75f
            };

            m_line = Line(startPos, endPos, thickness);

            return true;
        }
    }
    return false;
}

bool Game::CheckDiagonals() const
{
    const BoxStates playerState{static_cast<BoxStates>(m_player)};

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
        const float thickness{5.f};
        const Rectangle firstRec = m_boxes[0][0].second;
        const Vector2 startPos{
            firstRec.x + firstRec.width / 2.f - thickness * 3, 
            firstRec.y + firstRec.height / 2.f - thickness * 3
        };

        const Rectangle lastRec = m_boxes[m_boxes.size()-1][m_boxes.size()-1].second;
        const Vector2 endPos{
            lastRec.x + lastRec.width / 2.f,
            lastRec.y + lastRec.height / 2.f
        };

        m_line = Line(startPos, endPos, thickness);

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
        const float thickness{5.f};
        const size_t last{m_boxes.size()-1};
        const Vector2 startPos{
            m_boxes[0][last].second.x + m_boxes[0][last].second.width / 2.f - thickness * 4.3f,
            m_boxes[0][last].second.y + m_boxes[0][last].second.height / 2.f + thickness * 1.4f
        };
        const Vector2 endPos{
            m_boxes[last][0].second.x + m_boxes[last][0].second.width / 2.f + thickness * 1.4f,
            m_boxes[last][0].second.y + m_boxes[last][0].second.height / 2.f - thickness * 4.3f
        };

        m_line = Line(startPos, endPos, thickness);
    }

    return result;
}

bool Game::CheckVictory() const
{
    return this->CheckRows() || this->CheckColumns() || this->CheckDiagonals();
}

bool Game::CheckDraw() const
{
    for (const auto &subArray : m_boxes)
    {
        if (std::any_of(subArray.begin(), subArray.end(), [](auto pair){ return pair.first == BoxStates::NONE; }))
        {
            return false;
        }
    }
    return !this->CheckVictory();
}

void Game::Run()
{
    while (!WindowShouldClose() && !CheckVictory() && !CheckDraw())
    {
        this->Update();
        this->Draw();
    }

    if (CheckVictory())
    {
        m_text = "Player " + std::to_string(m_player) + " has won!";
        DrawGameOverScreen(m_text);
    }
    else if (CheckDraw())
    {
        DrawGameOverScreen("Draw!");
    }
}

void Game::Update()
{
    if (IsKeyPressed(KEY_F12))
    {
        TakeScreenshot("scr.png");
    }

    if (IsKeyPressed(KEY_ENTER))
    {
        m_darkMode = !m_darkMode;
    }

    if (!m_darkMode && m_bgColor != WHITE)
    {
        m_bgColor = WHITE;
    }
    else if (m_darkMode && m_bgColor != BLACK)
    {
        m_bgColor = BLACK;
    }

    for (auto &subArray : m_boxes)
    {
        for (auto &box : subArray)
        {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && (GetMouseX() >= box.second.x) && (GetMouseX() <= box.second.x + box.second.width) && 
                (GetMouseY() >= box.second.y) && (GetMouseY() <= box.second.y + box.second.height))
            {
                if (!m_gameBegan)
                {
                    m_gameBegan = true;
                }

                if (box.first == BoxStates::NONE)
                {
                    box.first = static_cast<BoxStates>(m_player);

                    PlaySound(((m_player == 1) ? m_sounds.at("player1") : m_sounds.at("player2")));

                    if (!CheckVictory())
                    {
                        m_player = (m_player == 1) ? 2 : 1;
                    }

                    m_text = "Player " + std::to_string(m_player) + "'s turn!";
                }
                else
                {
                    m_text = "Something was already placed in that box!";
                }
            }
        }
    }
}

void Game::DrawBoard() const
{
    for (const auto &subArray : m_boxes)
    {
        for (const auto &box : subArray)
        {
            DrawRectangleRec(box.second, BLUE);

            if (box.first == BoxStates::CROSS)
            {
                DrawTexture(m_textures.at("cross"), box.second.x + 5, box.second.y + 5, WHITE);
            }
            else if (box.first == BoxStates::CIRCLE)
            {
                DrawTexture(m_textures.at("circle"), box.second.x + 5, box.second.y + 5, WHITE);
            }
        }
    }
}

void Game::DrawTopText(const std::string &text, size_t size) const
{
    DrawText(
        text.c_str(), (GetScreenWidth() - MeasureText(text.c_str(), size)) / 2, 
        (GetScreenHeight() - GetScreenWidth() - size) / 2, size, (m_darkMode ? WHITE : BLACK)
    );
}

void Game::DrawGameOverScreen(const std::string &text) const
{
    int timer{static_cast<int>(GetFrameTime())};

    while (timer <= GetFPS())
    {
        timer++;
        
        BeginDrawing();

            ClearBackground(m_bgColor);
            this->DrawBoard();
            this->DrawTopText(text, 40);

            m_line.Draw((m_darkMode ? WHITE : BLACK));

        EndDrawing();
    }
}

void Game::Draw() const
{
    BeginDrawing();

        ClearBackground(m_bgColor);

        this->DrawBoard();
        
        if (!m_gameBegan) 
        {
            this->DrawTopText("Player 1 plays X, player 2 plays O", 30);
        }
        else
        {
            this->DrawTopText(m_text, ((m_text.length() > 16) ? 25 : 40));
        }

    EndDrawing();
}
