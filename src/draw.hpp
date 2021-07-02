#ifndef DRAW_HPP
#define DRAW_HPP

#include "precompiled.hpp"

bool operator==(const Color &color1, const Color &color2);
bool operator!=(const Color &color1, const Color &color2);

void DrawBoard(const std::array<std::array<char, 3>, 3> &board, const std::array<std::array<Rectangle, 3>, 3> &grid, 
               const std::array<char, 3> &states, const Texture2D &texBoard, const Texture2D &texCross, const Texture2D &texCircle);

void DrawUpperText(const std::string &text, size_t size, const Color& color);

void DrawGameOverScreen(const std::string &text, const Color &bgColor, const std::array<std::array<char, 3>, 3> &board, 
                        const std::array<std::array<Rectangle, 3>, 3> &grid, const std::array<char, 3> &states, const Texture2D &texBoard, 
                        const Texture2D& texCross, const Texture2D &texCircle);

#endif
