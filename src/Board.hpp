#ifndef BOARD_HPP
#define BOARD_HPP

#include "Line.hpp"

enum class BoxStates { NONE, CROSS, CIRCLE };

class Board
{
public:
	Board(float lineThickness);

	auto &GetBoxes()
	{
		return m_boxes;
	}

	bool CheckRows(int playerTurn) const;
    bool CheckColumns(int playerTurn) const;
    bool CheckDiagonals(int playerTurn) const;

	void Draw(const std::map<std::string, Texture2D> &textures) const;
	void DrawLine(const Color &color) const;

private:
	const float m_lineThickness;
	std::array<std::array<std::pair<BoxStates, Rectangle>, 3>, 3> m_boxes;
	mutable Line m_line;
};

#endif // BOARD_HPP
