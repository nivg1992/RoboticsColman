#include "SearchNode.h"

#include <math.h>

SearchNode::SearchNode(int x, int y) : X(x), Y(y) {
	//cout << "SearchNode.cpp: Creating node.. " << x << "," << y << endl;
}

SearchNode::SearchNode() : SearchNode(0, 0) {
}

// Heuristic distance between this and the goal node
double SearchNode::goalDistanceEstimate(SearchNode& goalNode) {
	return sqrt(pow(this->X - goalNode.X, 2) + pow(this->Y - goalNode.Y, 2));
}

bool SearchNode::isGoal(SearchNode& goalNode) {
	cout << "SearchNode.cpp: isGoal? " << X << "," << Y << endl;
	return X == goalNode.X && Y == goalNode.Y;
}

/**
 * Adds the cell as a successor if its not the previous one
 * and its free.
 */
void addIfNotBackwards(Cell* cell, Cell* previousCell, AStarSearch<SearchNode>* search) {
	// Don't add it if it isn't there.
	if (cell == NULL) return;

	int x = cell->getX();
	int y = cell->getY();

	cout << "SearchNode.cpp: " << "is " << x << "," << y << " free? " << cell->isFree() << endl;

	if (previousCell == NULL || (!cell->equalsTo(previousCell) && cell->isFree())) {
		SearchNode newNode = SearchNode(x, y);
		search->AddSuccessor(newNode);
	}
}

bool SearchNode::getSuccessors(AStarSearch<SearchNode>* search, AnotherMap* map, SearchNode* parentNode) {
	cout << "SearchNode.cpp: " << "searching successors for " << this->Y << "," << this->Y << endl;
	// Infinity!
	Cell* previousCell = NULL;

	if (parentNode) {
		previousCell = map->getResizedCell(parentNode->X, parentNode->Y);
	}

	SearchNode newNode;

	// push each possible move except allowing the search to go backwards

	Cell* neighbors[] = {
			map->getResizedCell(X - 1, Y),
			map->getResizedCell(X + 1, Y),
			map->getResizedCell(X, Y - 1),
			map->getResizedCell(X, Y + 1)
	};

	for (Cell* neighbor : neighbors) {
		addIfNotBackwards(neighbor, previousCell, search);
	}

	return true;
}

// given this node, what does it cost to move to successor. In the case
// of our map the answer is the map terrain value at this node since that is
// conceptually where we're moving
double SearchNode::getCost(SearchNode& successor, AnotherMap* map) {
	Cell* cell = map->getResizedCell(Y, X);
	CellType cost = cell->Cell_Cost;
	//delete cell;
	return (double)cost;
}

bool SearchNode::isSameState(SearchNode& rhs) {
	// same state in a maze search is simply when (x,y) are the same
	return X == rhs.X && Y == rhs.Y;
}

ostream& operator<<(ostream& os, const SearchNode& node) {
	os << "[" << node.X << "," << node.Y << "]";

	return os;
}
