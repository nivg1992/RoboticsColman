#include "Cell.h"
#include "Map.h"

using namespace std;

Cell::Cell(unsigned x, unsigned y, CellType cell_cost) {
	m_IsInit = false;
	m_X = x;
	m_Y = y;
	Cell_Cost = cell_cost;

	// cout << "Cell.cpp: " << x << "," << y << "," << cell_cost << endl;
}

Cell::Cell(const Cell& cell) {
	m_IsInit = cell.m_IsInit;
	m_X = cell.m_X;
	m_Y = cell.m_Y;
	Cell_Cost = cell.Cell_Cost;
	m_Neighbors = vector<Cell*>(cell.m_Neighbors);
}

Cell::Cell(const Cell* cell) {
	m_IsInit = cell->m_IsInit;
	m_X = cell->m_X;
	m_Y = cell->m_Y;
	Cell_Cost = cell->Cell_Cost;
	m_Neighbors = vector<Cell*>();
}

void Cell::init(vector<Cell*> neighbors) {
	if (m_IsInit) {
		return;
	}
	m_IsInit = true;
	m_Neighbors = vector<Cell*>(neighbors);
}

Cell::~Cell() {
	m_IsInit = false;
}

bool Cell::isFree() {
	cout << "Cell.cpp " << this->m_X << "," << this->m_Y << ": " << (double)this->Cell_Cost << endl;
	return this->Cell_Cost == CellType::TERRAIN;
}
