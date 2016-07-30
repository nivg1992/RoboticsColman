/*
 * AlternativeMap.cpp
 *
 *  Created on: Jun 20, 2015
 *      Author: colman
 */

#include "AnotherMap.h"
#include "Cell.h"
#include <stdio.h>
#include "../lib/lodepng.h"
#include "../Managers/ConfigurationManager.h"
#include "../Utils/MathUtil.h"

using namespace std;

char* colorFor(CellType type) {
	char r, g, b;
	switch (type) {
	case (CellType::TERRAIN):
		r = g = b = 255;
		break;
	case (CellType::WALL):
		r = g = b = 0;
		break;
	case (CellType::BLOATED_WALL):
		r = g = b = 100;
		break;
	case (CellType::PATH):
		r = 0;
		g = 140;
		b = 40;
		break;
	case (CellType::START):
		r = 0;
		g = 40;
		b = 140;
		break;
	case (CellType::DESTINATION):
		r = 140;
		g = 40;
		b = 0;
		break;
	}
	char* c = new char[3];
	c[0] = r;
	c[1] = g;
	c[2] = b;
	return c;
}

void saveFile(AnotherMap* map, string fileName, bool resized) {
	int gridSquare = map->gridHeight * map->gridWidth;
	if (!resized) {
		gridSquare = map->height * map->width;
	}
	unsigned char* image = new unsigned char[gridSquare * 4];
	for (int i = 0; i < gridSquare; i++) {
		CellType type;
		if (resized) {
			type = map->resizedGrid[i]->Cell_Cost;
		} else {
			type = map->grid[i]->Cell_Cost;
		}
		char* rgb = colorFor(type);
		image[i * 4] = rgb[0];
		image[i * 4 + 1] = rgb[1];
		image[i * 4 + 2] = rgb[2];
		image[i * 4 + 3] = 255;
		delete[] rgb;
	}
	lodepng::encode(fileName, image, resized ? map->gridWidth : map->width, resized ? map->gridHeight : map->height);
	delete image;
}

void loadFile(AnotherMap* map, string fileName) {
	cout << "Loading file '" << fileName << "'..." << endl;
	unsigned error = lodepng::decode(map->image, map->width, map->height,
			fileName);
	cout << "error:" << error << ", size: " << map->width << "x" << map->height
			<< endl;
}

void resizeGrid(AnotherMap* map) {
	// Calc grid size
	Managers::ConfigurationManager* config = map->config;
	float gridResolution = config->getPngGridResolution();
	float pixelPerCm = config->getPixelPerCm();
	unsigned gridCellSizeInPx = ceil(gridResolution / pixelPerCm);
	unsigned gridCols = floor(map->gridWidth * pixelPerCm / gridResolution);
	unsigned gridRows = floor(map->gridHeight * pixelPerCm / gridResolution);
	map->resizedGrid = std::vector<Cell*>(gridCols * gridRows);

	for (unsigned col = 0; col < gridCols; ++col) {
		for (unsigned row = 0; row < gridRows; ++row) {
			// defind white px counter
			unsigned pxWallCounter = 0, pxTerrainCounter = 0,
					pxBloatedWallCounter = 0;

			// find out from the png if cell is black or white
			for (unsigned pCol = 0; pCol < gridCellSizeInPx; ++pCol) {
				for (unsigned pRow = 0; pRow < gridCellSizeInPx; ++pRow) {
					Cell* cell = map->getCell(col * gridCellSizeInPx + pCol,
							row * gridCellSizeInPx + pRow);
					if (cell == NULL)
						continue;
					switch (cell->Cell_Cost) {
					case CellType::BLOATED_WALL:
						pxBloatedWallCounter++;
						break;

					case CellType::TERRAIN:
						pxTerrainCounter++;
						break;

					case CellType::WALL:
						pxWallCounter++;
						break;

					default:
						break;
					}
				}
			}
			CellType cellType;
			if (pxWallCounter > 0) {
				cellType = CellType::WALL;
			} else if (pxBloatedWallCounter >= pxTerrainCounter) {
				if (pxBloatedWallCounter > pxWallCounter) {
					cellType = CellType::BLOATED_WALL;
				} else {
					cellType = CellType::WALL;
				}
			} else {
				if (pxTerrainCounter > pxWallCounter) {
					cellType = CellType::TERRAIN;
				} else {
					cellType = CellType::WALL;
				}
			}
			cout << pxTerrainCounter << "," << pxWallCounter << ","
					<< pxBloatedWallCounter << endl;
			cout << (row*gridCols + col) << " ";
			map->resizedGrid[row * gridCols + col] = new Cell(col, row, cellType);
		}
	}

	cout << "YAY" << endl;

	map->gridHeight = gridRows;
	map->gridWidth = gridCols;
}

void bloatMap(AnotherMap* map, unsigned pxToBloat) {
	unsigned newWidth = map->gridWidth = map->width; //map->gridWidth = pxToBloat * map->width;
	unsigned newHeight = map->gridHeight = map->height; //map->gridHeight = pxToBloat * map->height;
	map->grid = vector<Cell*>(map->width * map->height);
	int i = 0;
	for (unsigned y = 0; y < newHeight; ++y) {
		for (unsigned x = 0; x < newWidth; ++x) {
			bool isWall = map->image[(y * map->width + x) * 4] == 0;
			map->grid[y * newWidth + x] = new Cell(x, y,
					isWall ? CellType::WALL : CellType::TERRAIN);
			i++;
		}
	}

	for (unsigned y = 0; y < newHeight; ++y) {
		for (unsigned x = 0; x < newWidth; ++x) {
			if (map->getCell(x, y)->Cell_Cost != CellType::WALL) {
				continue;
			}
			for (unsigned bloatY = 0; bloatY <= pxToBloat; ++bloatY) {
				for (unsigned bloatX = 0; bloatX <= pxToBloat; ++bloatX) {
					Cell* cell = map->getCell(x + bloatX - pxToBloat / 2,
							y + bloatY - pxToBloat / 2);
					if (cell != NULL && cell->Cell_Cost != CellType::WALL) {
						cell->Cell_Cost = CellType::BLOATED_WALL;
					}
				}
			}
		}
	}

	// Reduce the footprint.
	map->image.resize(1);
}

unsigned howMuchPxToBloat(float robotRadiusSize, float pngGridResolution) {
	return round(Utils::MathUtil::cmToPx(robotRadiusSize) * 7);
}

AnotherMap::AnotherMap(Managers::ConfigurationManager* config) {
	this->width = 1;
	this->height = 1;
	this->gridWidth = 1;
	this->gridHeight = 1;
	this->config = config;

	loadFile(this, config->getPngMapPath());
	bloatMap(this,
			howMuchPxToBloat(config->getRobotSize().RadiosSize(),
					config->getPngGridResolution()));
	resizeGrid(this);
	cout << "RESIZED TO " << this->gridWidth << "c" << this->gridHeight << endl;
	saveFile(this, "/tmp/holyfuck.png", true);

	cout << "NOT DEAD! YAY" << endl;
}

Cell* AnotherMap::getCell(unsigned x, unsigned y) {
	if (x < 0 || y < 0 || x >= this->width || y >= this->height) {
		return NULL;
	}
	return this->grid[y * this->width + x];
}

void AnotherMap::saveToFile(string fileName, bool resized) {
	return saveFile(this, fileName, resized);
}

Cell* AnotherMap::getResizedCell(unsigned x, unsigned y) {
	if (x < 0 || y < 0 || x >= this->gridWidth || y >= this->gridHeight) {
		return NULL;
	}
	return this->resizedGrid[y * this->gridWidth + x];
}

AnotherMap::~AnotherMap() {
	// TODO Auto-generated destructor stub
	for (Cell* cell : this->grid) {
		delete cell;
	}
}

