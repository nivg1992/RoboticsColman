#pragma once

#include <vector>
#include "Location.h"

using namespace std;

enum class CellType : unsigned char {
	TERRAIN = 0,
	BLOATED_WALL = 1,
	WALL = 2,
	PATH = 3,
	START = 4,
	DESTINATION = 5
};

class Cell {
public:
	static const unsigned NUM_NEIGHBORS = 8;
	CellType Cell_Cost;
	Cell(unsigned x, unsigned y, CellType cell_cost = CellType::TERRAIN);
	Cell(const Cell& cell);
	Cell(const Cell* cell);

	~Cell();

	void init(vector<Cell*> neighbors);

	inline Location getLocation() {
		return Location(this->m_X, this->m_Y, 0.0);
	}
	inline bool equalsTo(Cell* cell) {
		return (this->getX() == cell->getX() && this->getY() == cell->getY());
	}

	inline vector<Cell*> getNeighbors() {
		return m_Neighbors;
	};

	inline unsigned getX() {
		return m_X;
	};

	inline unsigned getY() {
		return m_Y;
	};

	inline bool getIsInit() {
		return m_IsInit;
	};

	bool isFree();

protected:
	bool m_IsInit;
	vector<Cell*> m_Neighbors;
	unsigned m_X;
	unsigned m_Y;
};

