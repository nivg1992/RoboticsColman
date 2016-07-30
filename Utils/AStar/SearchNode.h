#pragma once

#include "../../Models/Map.h"
#include "../../Models/AnotherMap.h"
#include "../stlastar.h"

class SearchNode
{
public:
	SearchNode();
	SearchNode(int x, int y);

	double goalDistanceEstimate(SearchNode& goalNode);
	bool isGoal(SearchNode& goalNode);
	bool getSuccessors(AStarSearch<SearchNode>* search, AnotherMap* map, SearchNode* parentNode);
	double getCost(SearchNode& successor, AnotherMap* map);
	bool isSameState(SearchNode& rhs);

	inline Cell* toMapCell(AnotherMap* map) {
		return map->getResizedCell(this->X, this->Y);
	}

	friend ostream& operator<<(ostream& os, const SearchNode& cell);

	int X;
	int Y;
};
