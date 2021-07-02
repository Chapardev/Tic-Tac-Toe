#ifndef CHECK_HPP
#define CHECK_HPP

#include "precompiled.hpp"

bool CheckRows(const std::array<std::array<char, 3>, 3>& board, const std::array<char, 3>& states, int player);
bool CheckColumns(const std::array<std::array<char, 3>, 3>& board, const std::array<char, 3>& states, int player);
bool CheckDiagonals(const std::array<std::array<char, 3>, 3>& board, const std::array<char, 3>& states, int player);

bool CheckVictory(const std::array<std::array<char, 3>, 3> &board, const std::array<char, 3> &states, int player);
bool CheckDraw(const std::array<std::array<char, 3>, 3>& board, const std::array<char, 3>& states, int player);

#endif
