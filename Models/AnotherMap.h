/*
 * AlternativeMap.h
 *
 *  Created on: Jun 20, 2015
 *      Author: colman
 */

#ifndef ALTERNATIVEMAP_H_
#define ALTERNATIVEMAP_H_
#pragma once

#include <stdio.h>
#include "Cell.h"
#include <string>
#include "../Models/Size.h"
#include "../Managers/ConfigurationManager.h"

using namespace std;

class AnotherMap {
public:
	AnotherMap(Managers::ConfigurationManager* config);
	virtual ~AnotherMap();
	Cell* getCell(unsigned x, unsigned y);
	Cell* getResizedCell(unsigned x, unsigned y);
	Cell* getResizedCellFromImageCoords(unsigned x, unsigned y) {
		return this->getResizedCell(
			x * this->gridWidth / this->width,
			y * this->gridHeight / this->height
		);
	}
	void saveToFile(string fileName, bool resized = false);
	unsigned int height;
	unsigned int width;
	unsigned int gridWidth;
	unsigned int gridHeight;
	vector<unsigned char> image;
	vector<Cell*> grid;
	Managers::ConfigurationManager* config;
	vector<Cell*> resizedGrid;
};

#endif /* ALTERNATIVEMAP_H_ */
