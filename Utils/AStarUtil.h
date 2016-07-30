#pragma once

#include "../Models/AnotherMap.h";
#include <vector>
#include "stlastar.h"
#include "./AStar/SearchNode.h"
#include "../Models/Cell.h"

using namespace std;

namespace Utils {
  class AStarUtil {
  public:
	  AStarUtil(AnotherMap* map) : map(map), search(NULL) {
		  cout << "AStarUtil.h: Creating a map." << endl;
	  }
	  vector<Cell*> findPath(Cell* start, Cell* destination);
	  static void testWithMap(AnotherMap* m) {
			AStarUtil astar(m);
			Cell* start = m->getResizedCell(40, 30);
			Cell* destination = m->getResizedCell(60, 30);
			cout << "main.cpp: " << "start: [" << (start->getX()) << "," << (start->getY()) << "]" << endl;
			cout << "main.cpp: " << "destination: [" << destination->getX() << "," << destination->getY() << "]" << endl;
			vector<Cell*> path = astar.findPath(start, destination);
			cout << "main.cpp: " << "finished." << endl;
			cout << "main.cpp: " << "PATH LENGTH: " << path.size() << endl;

			for (Cell* cell : path) {
				cout << "main.cpp: " << "[" << cell->getX() << "," << cell->getY() << "]" << endl;
				cell->Cell_Cost = CellType::PATH;
			}

			start->Cell_Cost = CellType::START;
			destination->Cell_Cost = CellType::DESTINATION;

			m->saveToFile("/tmp/wtf-with-path.png", true);
	  }
  protected:
	  AnotherMap* map;
	  AStarSearch<SearchNode> search;
	  vector<Cell*> buildPath();
  };
}
