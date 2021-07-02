#include "draw.hpp"

bool operator==(const Color &color1, const Color &color2)
{
    return ((color1.r == color2.r) && (color1.g == color2.g) && (color1.b == color2.b));
}

bool operator!=(const Color &color1, const Color &color2)
{
    return !(color1 == color2);
}

void DrawBoard(const std::array<std::array<char, 3>, 3> &board, const std::array<std::array<Rectangle, 3>, 3> &grid, 
               const std::array<char, 3> &states, const Texture2D &texBoard, const Texture2D &texCross, const Texture2D &texCircle)
{
    DrawTexture(texBoard, 0, GetScreenHeight() - texBoard.height, WHITE);

    for (size_t i = 0; i < board.size(); i++)
    {
        for (size_t j = 0; j < board[i].size(); j++)
        {
            if (board[i][j] == states[1])
                DrawTexture(texCross, grid[i][j].x + 5, grid[i][j].y + 5, WHITE);
            else if (board[i][j] == states[2])
                DrawTexture(texCircle, grid[i][j].x + 5, grid[i][j].y + 5, WHITE);
        }
    }
}

void DrawUpperText(const std::string &text, size_t size, const Color& color)
{
    const char *cText = text.c_str();
    DrawText(cText, (GetScreenWidth() - MeasureText(cText, size)) / 2, (GetScreenHeight() - GetScreenWidth() - size) / 2, size, color);
}

void DrawGameOverScreen(const std::string &text, const Color &bgColor, const std::array<std::array<char, 3>, 3> &board, 
                        const std::array<std::array<Rectangle, 3>, 3> &grid, const std::array<char, 3> &states, const Texture2D &texBoard, 
                        const Texture2D& texCross, const Texture2D &texCircle)
{
    const Color textColor = (bgColor == WHITE) ? BLACK : WHITE;
    int timer = (int)GetFrameTime();

    while (timer <= GetFPS())
    {
        timer++;
        
        BeginDrawing();

            ClearBackground(bgColor);
            DrawBoard(board, grid, states, texBoard, texCross, texCircle);
            DrawUpperText(text, 40, textColor);

        EndDrawing();
    }
}
