#include "Game.hpp"

bool operator==(const Color &left, const Color &right)
{
    return ((left.r == right.r) && (left.g == right.g) && (left.b == right.b));
}

bool operator!=(const Color &left, const Color &right)
{
    return !(left == right);
}

void Game::_InitArrays()
{
    const int lineThickness = 5;
    const int boxWidth = (GetScreenWidth() - lineThickness) / 3;
    const int boxHeight = (GetScreenWidth() - lineThickness) / 3;

    for (size_t i = 0; i < m_board.size(); i++)
        for (size_t j = 0; j < m_board[i].size(); j++)
            m_board[i][j] = BoxStates::NONE;

    for (size_t i = 0; i < m_grid.size(); i++)
    {
        for (size_t j = 0; j < m_grid[i].size(); j++)
        {
            m_grid[i][j].width = boxWidth;
            m_grid[i][j].height = boxHeight;

            m_grid[i][j].x = (boxWidth + lineThickness) * i;
            m_grid[i][j].y = (GetScreenHeight() - GetScreenWidth()) + (boxHeight + lineThickness) * j;
        }
    }
}

void Game::_LoadGraphics()
{
    m_imgIcon = LoadImage("../assets/cross.png");
    SetWindowIcon(m_imgIcon);
    UnloadImage(m_imgIcon);

    m_texCross = LoadTexture("../assets/cross.png");
    m_texCircle = LoadTexture("../assets/circle.png");
}

void Game::_LoadSounds()
{
    m_player1Sound = LoadSound("../assets/player1.wav");
    m_player2Sound = LoadSound("../assets/player2.wav");
}

Game::Game() : m_player(1), m_gameBegan(false), m_darkMode(false), m_bgColor(WHITE)
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
    UnloadSound(m_player1Sound);
    UnloadSound(m_player2Sound);

    UnloadTexture(m_texCircle);
    UnloadTexture(m_texCross);

    CloseAudioDevice();
    CloseWindow();
}

bool Game::CheckRows()
{
    BoxStates playerState = static_cast<BoxStates>(m_player);
    for (size_t i = 0; i < m_board.size(); i++)
    {
        if (m_board[0][i] == playerState && m_board[1][i] == playerState && m_board[2][i] == playerState)
        {
            const float thickness = 5.f;

            const Vector2 startPos = {
                m_grid[0][i].x + m_grid[0][i].width / 4.f, 
                m_grid[0][i].y + m_grid[0][i].height / 2.f - thickness
            };
            
            const Vector2 endPos = {
                m_grid[2][i].x + m_grid[2][i].width * 0.75f,
                m_grid[2][i].y + m_grid[2][i].height / 2.f - thickness
            };

            m_line = Line(startPos, endPos, thickness);

            return true;
        }
    }
    return false;
}

bool Game::CheckColumns()
{
    BoxStates playerState = static_cast<BoxStates>(m_player);
    for (size_t i = 0; i < m_board.size(); i++)
    {
        if (m_board[i][0] == playerState && m_board[i][1] == playerState && m_board[i][2] == playerState)
        {
            const float thickness = 5.f;

            const Vector2 startPos = {
                m_grid[i][0].x + m_grid[i][0].width / 2.f - thickness, 
                m_grid[i][0].y + m_grid[i][0].height / 4.f
            };
            
            const Vector2 endPos = {
                m_grid[i][2].x + m_grid[i][2].width / 2.f - thickness,
                m_grid[i][2].y + m_grid[i][2].height * 0.75f
            };

            m_line = Line(startPos, endPos, thickness);

            return true;
        }
    }
    return false;
}

bool Game::CheckDiagonals()
{
    BoxStates playerState = static_cast<BoxStates>(m_player);

    bool result = true;
    for (size_t i = 0; i < m_board.size(); i++)
        if (m_board[i][i] != playerState)
            result = false;
    if (result) 
    {
        const float thickness = 5.f;

        const Vector2 startPos = {
            m_grid[0][0].x + m_grid[0][0].width / 2.f - thickness * 3, 
            m_grid[0][0].y + m_grid[0][0].height / 2.f - thickness * 3
        };
        
        const Vector2 endPos = {
            m_grid[2][2].x + m_grid[2][2].width / 2.f,
            m_grid[2][2].y + m_grid[2][2].height / 2.f
        };

        m_line = Line(startPos, endPos, thickness);

        return result;
    }
    
    result = true;
    for (size_t i = 0; i < m_board.size(); i++)
        if (m_board[m_board.size() - i - 1][i] != playerState)
            result = false;

    if (result)
    {
        const float thickness = 5.f;

        const Vector2 startPos = {
            m_grid[0][2].x + m_grid[0][2].width / 2.f - thickness * 4.3f,
            m_grid[0][2].y + m_grid[0][2].height / 2.f + thickness * 1.4f
        };
        
        const Vector2 endPos = {
            m_grid[2][0].x + m_grid[2][0].width / 2.f + thickness * 1.4f,
            m_grid[2][0].y + m_grid[2][0].height / 2.f - thickness * 4.3f
        };

        m_line = Line(startPos, endPos, thickness);
    }

    return result;
}

bool Game::CheckVictory()
{
    return (this->CheckRows() || this->CheckColumns() || this->CheckDiagonals());
}

bool Game::CheckDraw()
{
    for (size_t i = 0; i < m_board.size(); i++)
        for (size_t j = 0; j < m_board[i].size(); j++)
            if (m_board[i][j] == BoxStates::NONE)
                return false;
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
        DrawGameOverScreen("Draw!");
}

void Game::Update()
{
    if (IsKeyPressed(KEY_F12)) TakeScreenshot("scr.png");
    if (IsKeyPressed(KEY_ENTER)) m_darkMode = !m_darkMode;

    if (!m_darkMode && m_bgColor != WHITE) m_bgColor = WHITE;
    else if (m_darkMode && m_bgColor != BLACK) m_bgColor = BLACK;

    for (size_t i = 0; i < m_grid.size(); i++)
    {
        for (size_t j = 0; j < m_grid[i].size(); j++)
        {
            if ((GetMouseX() >= m_grid[i][j].x) && (GetMouseX() <= m_grid[i][j].x + m_grid[i][j].width) && 
                (GetMouseY() >= m_grid[i][j].y) && (GetMouseY() <= m_grid[i][j].y + m_grid[i][j].height) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                if (!m_gameBegan) m_gameBegan = true;
                if (m_board[i][j] == BoxStates::NONE)
                {
                    m_board[i][j] = static_cast<BoxStates>(m_player);

                    PlaySound(((m_player == 1) ? m_player1Sound : m_player2Sound));

                    if (!CheckVictory())
                        m_player = (m_player == 1) ? 2 : 1;

                    m_text = "Player " + std::to_string(m_player) + "'s turn!";
                }
                else m_text = "Something was already placed in that box!";
            }
        }
    }
}

void Game::DrawBoard()
{
    for (size_t i = 0; i < m_board.size(); i++)
    {
        for (size_t j = 0; j < m_board[i].size(); j++)
        {
            DrawRectangleRec(m_grid[i][j], BLUE);

            if (m_board[i][j] == BoxStates::CROSS)
                DrawTexture(m_texCross, m_grid[i][j].x + 5, m_grid[i][j].y + 5, WHITE);
            else if (m_board[i][j] == BoxStates::CIRCLE)
                DrawTexture(m_texCircle, m_grid[i][j].x + 5, m_grid[i][j].y + 5, WHITE);
        }
    }
}

void Game::DrawTopText(const std::string &text, const size_t size)
{
    DrawText(
        text.c_str(), (GetScreenWidth() - MeasureText(text.c_str(), size)) / 2, 
        (GetScreenHeight() - GetScreenWidth() - size) / 2, size, (m_darkMode ? WHITE : BLACK)
    );
}

void Game::DrawGameOverScreen(const std::string &text)
{
    int timer = (int)GetFrameTime();

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

void Game::Draw()
{
    BeginDrawing();

        ClearBackground(m_bgColor);

        this->DrawBoard();
        
        if (m_gameBegan) 
            this->DrawTopText(m_text, ((m_text.length() > 16) ? 25 : 40));
        else
            this->DrawTopText("Player 1 plays X, player 2 plays O", 30);

    EndDrawing();
}
