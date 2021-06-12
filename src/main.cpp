#include "check.hpp"
#include "draw.hpp"
#include <iostream>

int main()
{
    const int screenWidth = 600;
    const int screenHeight = 700;
    const int fps = 60;
    
    const int lineThickness = 5;
    const int side = 3;

    const int boxWidth = (screenWidth - lineThickness) / side;
    const int boxHeight = (screenWidth - lineThickness) / side;

    const char none = ' ', cross = 'X', circle = 'O';
    const std::array<char, side> states = {none, cross, circle};

    std::array<std::array<Rectangle, side>, side> grid;
    for (size_t i = 0; i < grid.size(); i++)
    {
        for (size_t j = 0; j < grid[i].size(); j++)
        {
            grid[i][j].width = boxWidth;
            grid[i][j].height = boxHeight;

            grid[i][j].x = (boxWidth + lineThickness) * i;
            grid[i][j].y = (screenHeight - screenWidth) + (boxHeight + lineThickness) * j;
        }
    }

    std::array<std::array<char, side>, side> board;
    for (size_t i = 0; i < board.size(); i++)
        for (size_t j = 0; j < board[i].size(); j++)
            board[i][j] = none;

    int player = 1;
    bool gameBegan = false, darkMode = false;
    Color bgColor = WHITE;
    std::string text = "";

    InitWindow(screenWidth, screenHeight, "Tic Tac Toe");

    Image imgIcon = LoadImage("../assets/cross.png");
    SetWindowIcon(imgIcon);
    UnloadImage(imgIcon);

    Texture2D texBoard = LoadTexture("../assets/board.png");
    Texture2D texCross = LoadTexture("../assets/cross.png");
    Texture2D texCircle = LoadTexture("../assets/circle.png");

    SetTargetFPS(fps);

    while (!WindowShouldClose() && !CheckVictory<side>(board, states, player) && !CheckDraw<side>(board, states, player))
    {
        if (IsKeyPressed(KEY_F12)) TakeScreenshot("scr.png");
        if (IsKeyPressed(KEY_ENTER)) darkMode = !darkMode;

        if (!darkMode && bgColor != WHITE) bgColor = WHITE;
        else if (darkMode && bgColor != BLACK) bgColor = BLACK;

        for (size_t i = 0; i < grid.size(); i++)
        {
            for (size_t j = 0; j < grid[i].size(); j++)
            {
                if ((GetMouseX() >= grid[i][j].x) && (GetMouseX() <= grid[i][j].x + grid[i][j].width) && 
                    (GetMouseY() >= grid[i][j].y) && (GetMouseY() <= grid[i][j].y + grid[i][j].height) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                {
                    if (!gameBegan) gameBegan = true;
                    if (board[i][j] == none)
                    {
                        board[i][j] = states[player];
                        if (!CheckVictory<side>(board, states, player))
                            player = (player == 1) ? 2 : 1;
                        text = "Player " + std::to_string(player) + "'s turn!";
                    }
                    else text = "Something was already placed in that box!";
                }
            }
        }

        BeginDrawing();

            ClearBackground(bgColor);
            DrawBoard<side>(board, grid, states, texBoard, texCross, texCircle);

            if (gameBegan) DrawUpperText(text, ((text.length() > 16) ? 25 : 40), (darkMode ? WHITE : BLACK));
            else DrawUpperText("Player 1 plays X, player 2 plays O", 30, (darkMode ? WHITE : BLACK));

        EndDrawing();
    }

    if (CheckVictory<side>(board, states, player))
    {
        text = "Player " + std::to_string(player) + " has won!";
        DrawGameOverScreen<side>(fps, text, bgColor, board, grid, states, texBoard, texCross, texCircle);
    }
    else if (CheckDraw<side>(board, states, player)) 
        DrawGameOverScreen<side>(fps, "Draw!", bgColor, board, grid, states, texBoard, texCross, texCircle);

    UnloadTexture(texCircle);
    UnloadTexture(texCross);
    UnloadTexture(texBoard);

    CloseWindow();

    return 0;
}
