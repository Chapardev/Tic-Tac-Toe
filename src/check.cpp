#include "check.hpp"

bool CheckRows(const std::array<std::array<BoxStates, 3>, 3>& board, int player)
{
    BoxStates playerState = static_cast<BoxStates>(player);
    for (size_t i = 0; i < board.size(); i++)
        if (board[0][i] == playerState && board[1][i] == playerState && board[2][i] == playerState)
            return true;
    return false;
}

bool CheckColumns(const std::array<std::array<BoxStates, 3>, 3>& board, int player)
{
    BoxStates playerState = static_cast<BoxStates>(player);
    for (size_t i = 0; i < board.size(); i++)
        if (board[i][0] == playerState && board[i][1] == playerState && board[i][2] == playerState)
            return true;
    return false;
}

bool CheckDiagonals(const std::array<std::array<BoxStates, 3>, 3>& board, int player)
{
    BoxStates playerState = static_cast<BoxStates>(player);

    bool result = true;
    for (size_t i = 0; i < board.size(); i++)
        if (board[i][i] != playerState)
            result = false;
    if (result) 
        return result;
    
    result = true;
    for (size_t i = 0; i < board.size(); i++)
        if (board[board.size() - i - 1][i] != playerState)
            result = false;
    return result;
}

bool CheckVictory(const std::array<std::array<BoxStates, 3>, 3> &board, int player)
{
    return CheckRows(board, player) || CheckColumns(board, player) || CheckDiagonals(board, player);
}

bool CheckDraw(const std::array<std::array<BoxStates, 3>, 3>& board, int player)
{
    for (size_t i = 0; i < board.size(); i++)
        for (size_t j = 0; j < board[i].size(); j++)
            if (board[i][j] == BoxStates::NONE)
                return false;
    return !CheckVictory(board, player);
}
