#include "game.hpp"

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

    m_texBoard = LoadTexture("../assets/board.png");
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
    UnloadTexture(m_texBoard);

    CloseAudioDevice();
    CloseWindow();
}

void Game::Run()
{
    while (!WindowShouldClose() && !CheckVictory(m_board, m_player) && !CheckDraw(m_board, m_player))
    {
        this->Update();
        this->Draw();
    }

    if (CheckVictory(m_board, m_player))
    {
        m_text = "Player " + std::to_string(m_player) + " has won!";
        DrawGameOverScreen(m_text, m_bgColor, m_board, m_grid, m_texBoard, m_texCross, m_texCircle);
    }
    else if (CheckDraw(m_board, m_player))
        DrawGameOverScreen("Draw!", m_bgColor, m_board, m_grid, m_texBoard, m_texCross, m_texCircle);
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

                    if (!CheckVictory(m_board, m_player))
                        m_player = (m_player == 1) ? 2 : 1;

                    m_text = "Player " + std::to_string(m_player) + "'s turn!";
                }
                else m_text = "Something was already placed in that box!";
            }
        }
    }
}

void Game::Draw()
{
    BeginDrawing();

        ClearBackground(m_bgColor);
        DrawBoard(m_board, m_grid, m_texBoard, m_texCross, m_texCircle);

        if (m_gameBegan) DrawUpperText(m_text, ((m_text.length() > 16) ? 25 : 40), (m_darkMode ? WHITE : BLACK));
        else DrawUpperText("Player 1 plays X, player 2 plays O", 30, (m_darkMode ? WHITE : BLACK));

    EndDrawing();
}
