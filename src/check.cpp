#include "check.hpp"

bool CheckRows(const std::array<std::array<char, 3>, 3>& board, const std::array<char, 3>& states, int player)
{
    for (size_t i = 0; i < board.size(); i++)
        if (board[0][i] == states[player] && board[1][i] == states[player] && board[2][i] == states[player])
            return true;
    return false;
}

bool CheckColumns(const std::array<std::array<char, 3>, 3>& board, const std::array<char, 3>& states, int player)
{
    for (size_t i = 0; i < board.size(); i++)
        if (board[i][0] == states[player] && board[i][1] == states[player] && board[i][2] == states[player])
            return true;
    return false;
}

bool CheckDiagonals(const std::array<std::array<char, 3>, 3>& board, const std::array<char, 3>& states, int player)
{
    bool result = true;
    for (size_t i = 0; i < board.size(); i++)
        if (board[i][i] != states[player])
            result = false;
    if (result) 
        return result;
    
    result = true;
    for (size_t i = 0; i < board.size(); i++)
        if (board[board.size() - i - 1][i] != states[player])
            result = false;
    return result;
}

bool CheckVictory(const std::array<std::array<char, 3>, 3> &board, const std::array<char, 3> &states, int player)
{
    return CheckRows(board, states, player) || CheckColumns(board, states, player) || CheckDiagonals(board, states, player);
}

bool CheckDraw(const std::array<std::array<char, 3>, 3>& board, const std::array<char, 3>& states, int player)
{
    for (size_t i = 0; i < board.size(); i++)
        for (size_t j = 0; j < board[i].size(); j++)
            if (board[i][j] == states[0])
                return false;
    return !CheckVictory(board, states, player);
}
