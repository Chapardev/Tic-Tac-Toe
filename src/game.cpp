#include "Game.hpp"

bool operator==(const Color &left, const Color &right)
{
    return (left.r == right.r) && (left.g == right.g) && (left.b == right.b);
}

bool operator!=(const Color &left, const Color &right)
{
    return !(left == right);
}

void Game::_LoadGraphics()
{
    Image m_imgIcon = LoadImage("../assets/cross.png");
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

    m_board = std::make_unique<Board>(5.f);

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

bool Game::CheckVictory() const
{
    return m_board->CheckRows(m_player) || m_board->CheckColumns(m_player) || m_board->CheckDiagonals(m_player);
}

bool Game::CheckDraw() const
{
    for (const auto &subArray : m_board->GetBoxes())
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

void Game::UpdateKeys()
{
    if (IsKeyPressed(KEY_F12))
    {
        TakeScreenshot("scr.png");
    }

    if (IsKeyPressed(KEY_ENTER))
    {
        m_darkMode = !m_darkMode;
    }
}

void Game::UpdateBgColor()
{
    if (m_bgColor != WHITE && !m_darkMode)
    {
        m_bgColor = WHITE;
    }
    else if (m_bgColor != BLACK && m_darkMode)
    {
        m_bgColor = BLACK;
    }
}

void Game::Update()
{
    this->UpdateKeys();

    this->UpdateBgColor();

    for (auto &subArray : m_board->GetBoxes())
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
            
            m_board->Draw(m_textures);

            this->DrawTopText(text, 40);
            
            m_board->DrawLine((m_darkMode ? WHITE : BLACK));

        EndDrawing();
    }
}

void Game::Draw() const
{
    BeginDrawing();

        ClearBackground(m_bgColor);

        m_board->Draw(m_textures);
        
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
