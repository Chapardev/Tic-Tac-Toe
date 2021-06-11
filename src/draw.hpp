#ifndef DRAW_HPP
#define DRAW_HPP

#include <array>
#include <iostream>
#include "raylib.h"

template<size_t N>
void DrawBoard(const std::array<std::array<char, N>, N> &board, const std::array<std::array<Rectangle, N>, N> &grid, 
               const std::array<char, N> &states, const Texture2D &texBoard, const Texture2D &texCross, const Texture2D &texCircle)
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

void DrawUpperText(const char *text, size_t size=40, const Color& color=BLACK)
{
    DrawText(text, (GetScreenWidth() - MeasureText(text, size)) / 2, (GetScreenHeight() - GetScreenWidth() - size) / 2, size, color);
}

template<size_t N>
void DrawGameOverScreen(int fps, const char *text, const std::array<std::array<char, N>, N> &board, const std::array<std::array<Rectangle, N>, N> &grid, 
                        const std::array<char, N> &states, const Texture2D &texBoard, const Texture2D& texCross, const Texture2D &texCircle)
{
    int timer = (int)GetFrameTime();
    while (timer <= fps)
    {
        timer++;
        
        BeginDrawing();

            ClearBackground(WHITE);
            DrawBoard<N>(board, grid, states, texBoard, texCross, texCircle);
            DrawUpperText(text);

        EndDrawing();
    }
}

#endif
