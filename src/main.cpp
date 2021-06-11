#include "check.hpp"
#include "draw.hpp"

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

    std::array<std::array<Rectangle, side>, side> grid {{
        {Rectangle{0}, Rectangle{0}, Rectangle{0}},
        {Rectangle{0}, Rectangle{0}, Rectangle{0}},
        {Rectangle{0}, Rectangle{0}, Rectangle{0}}
    }};

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

    std::array<std::array<char, side>, side> board {{
        {none, none, none},
        {none, none, none},
        {none, none, none}
    }};

    int player = 1;
    bool gameBegan = false, alreadyPlaced = false;

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
                        alreadyPlaced = false;
                    }
                    else if (!alreadyPlaced) alreadyPlaced = true;
                }
            }
        }

        BeginDrawing();

            ClearBackground(WHITE);
            DrawBoard<side>(board, grid, states, texBoard, texCross, texCircle);

            if (gameBegan)
            {
                if (!alreadyPlaced)
                {
                    if (player == 1) DrawUpperText("Player 1's turn!");
                    else DrawUpperText("Player 2's turn!");
                }
                else DrawUpperText("Something was already placed in that box!", 25);
            }
            else DrawUpperText("Player 1 plays X, player 2 plays O", 30);

        EndDrawing();
    }

    if (CheckVictory<side>(board, states, player))
    {
        const char *text = (player == 1) ? "Player 1 has won!" : "Player 2 has won!";
        DrawGameOverScreen<side>(fps, text, board, grid, states, texBoard, texCross, texCircle);
    }
    else if (CheckDraw<side>(board, states, player)) 
        DrawGameOverScreen<side>(fps, "Draw!", board, grid, states, texBoard, texCross, texCircle);

    UnloadTexture(texCircle);
    UnloadTexture(texCross);
    UnloadTexture(texBoard);

    CloseWindow();

    return 0;
}
