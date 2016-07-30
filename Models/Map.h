#pragma once
#include <vector>
#include "../Managers/ConfigurationManager.h"
#include "../Utils/pngUtil.h"
#include <math.h>
#include "Cell.h"
#include "../lib/lodepng.h"

using namespace std;
using namespace Managers;

class Map
{
public:
	enum PXTYPE {FREE=255, OPSTICAL=0, GRAY=100};
	unsigned m_Rows;
	unsigned m_Cols;
	unsigned pngWidth;
	unsigned pngHeight;
	Map(const char* filename);
	Map(unsigned Rows,unsigned Cols);
	~Map();

	void PrintMap(const char* filename);

	inline unsigned getCols() {
		return m_Cols;
	};

	inline unsigned getRows() {
		return m_Rows;
	};

	Cell* getCell(int row, int col) const;
	Cell* pointToGrid(unsigned x,unsigned y);


protected:

	vector<vector<Cell*> > m_Cells;
	std::vector<unsigned char> Grid;
	std::vector<unsigned char> pngMap;
	//std::vector<unsigned char> RegGrid;

private:

	void initMap(const char* filename);
	std::vector<unsigned char> CreatGridFromMap(const std::vector<unsigned char> PngMap,unsigned MapHeight,unsigned MapWidth, float GridResolutionCm, float PixelPerCm, unsigned &GridCols, unsigned &GridRows);
};
