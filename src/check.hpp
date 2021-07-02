#ifndef CHECK_HPP
#define CHECK_HPP

#include "precompiled.hpp"
bool CheckRows(const std::array<std::array<BoxStates, 3>, 3>& board, int player);
bool CheckColumns(const std::array<std::array<BoxStates, 3>, 3>& board, int player);
bool CheckDiagonals(const std::array<std::array<BoxStates, 3>, 3>& board, int player);

bool CheckVictory(const std::array<std::array<BoxStates, 3>, 3> &board, int player);
bool CheckDraw(const std::array<std::array<BoxStates, 3>, 3>& board, int player);

#endif
