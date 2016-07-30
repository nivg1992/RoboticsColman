#include "Map.h"

using namespace std;

Map::Map(const char* filename) {
	initMap(filename);
}

Map::Map(unsigned Cols, unsigned Rows) {
	this->m_Cols = Cols;
	this->m_Rows = Rows;
	this->Grid.resize(Rows* Cols);
	//this->RegGrid.resize(Rows* Cols);
}

void Map::initMap(const char* filename) {
	std::vector<unsigned char> Image;
	//std::vector<unsigned char> FatImage;
	unsigned width, height;
	unsigned x, y, bX, bY;

	// Get the config
	ConfigurationManager* config = ConfigurationManager::GetInstance();

	//decode
	unsigned error = lodepng::decode(Image, this->pngWidth, this->pngHeight,config->getPngMapPath());

	//if there's an error, display it
	if (error)
		std::cout << "Map.cpp: " << "decoder error " << error << ": "
				<< lodepng_error_text(error) << std::endl;

	// calc the size of the robot in pic px
	unsigned PxToBlow = ceil(
			config->getRobotSize().RadiosSize()
					/ config->getPixelPerCm() / 2);

	// run on the map and find the
	for (y = 0; y < height; y++)
		for (x = 0; x < width; x++) {
			if (Image[y * width * 4 + x * 4 + 0]
					* Image[y * width * 4 + x * 4 + 1]
					* Image[y * width * 4 + x * 4 + 2] == PXTYPE::OPSTICAL){ // if not bLACK = WHITE/grey

			// add oppstical to the fat img
			for (bX = std::max(x - PxToBlow, static_cast<unsigned int>(0));
					bX < PxToBlow + x; bX++)
				for (bY = std::max(y - PxToBlow, static_cast<unsigned int>(0));
						bY < PxToBlow + y; bY++) {
					// debug
					//cout << "X : " << bX << " Y : "<< bY <<" cell : " << bY * width * 4 + bX * 4 + 0 << " value : " << (int)Image[bY * width * 4 + bX * 4 + 0] << endl;
					if (!(Image[bY * width * 4 + bX * 4 + 0] == PXTYPE::OPSTICAL))
					{
						Image[bY * width * 4 + bX * 4 + 0] = static_cast<char>(PXTYPE::GRAY);
						Image[bY * width * 4 + bX * 4 + 1] = static_cast<char>(PXTYPE::GRAY);
						Image[bY * width * 4 + bX * 4 + 2] = static_cast<char>(PXTYPE::GRAY);
						Image[bY * width * 4 + bX * 4 + 3] = static_cast<char>(255);
					}
				}
			}
		}




	// create grid from the fat and regular map

	this->Grid = this->CreatGridFromMap(Image, height, width,
			config->getPngGridResolution(), config->getPixelPerCm(),
			this->m_Cols, this->m_Rows);

	// encode the map -- FLY
	//encodeOneStep("Grid2.png", Image, width, height);

	// Free Image Memory
	Image.clear();
	vector<unsigned char>().swap(Image);
//	this->RegGrid = this->CreatGridFromMap(image, height, width,
//			config->getPngGridResolution(), config->getPixelPerCm(),
//			this->m_Cols, this->m_Rows);

}

std::vector<unsigned char> Map::CreatGridFromMap(const std::vector<unsigned char> PngMap,
		unsigned MapHeight, unsigned MapWidth, float GridResolutionCm,
		float PixelPerCm, unsigned& GridCols, unsigned& GridRows) {

	// Calc grid size
	unsigned GridCellSizeInPx = ceil(GridResolutionCm / PixelPerCm);
	GridCols = floor(MapWidth * PixelPerCm / GridResolutionCm);
	GridRows = floor(MapHeight * PixelPerCm / GridResolutionCm);

	//crate the grid
	std::vector<unsigned char> Grid;
	Grid.resize(GridCols * GridRows);

	for (unsigned i = 0; i < GridCols; ++i) {
		for (unsigned j = 0; j < GridRows; ++j) {

			// defind white px counter
			unsigned PxOpsticalConuter,PxFreeConuter,PxGrayCounter = 0;

			// find out from the png if cell is black or white
			for (unsigned pI = 0; pI < GridCellSizeInPx; ++pI) {
				for (unsigned pJ = 0; pJ < GridCellSizeInPx; ++pJ) {
//					if (PngMap[(i * GridCellSizeInPx + pI) * 4 + (j * GridCellSizeInPx + pJ)* MapWidth * 4] != 255) {
//						PxBlackConuter++;
//					}
					switch (PngMap[(i * GridCellSizeInPx + pI) * 4 + (j * GridCellSizeInPx + pJ)* MapWidth * 4]){
						case static_cast<char>(Map::GRAY):
							PxGrayCounter++;
							break;

						case static_cast<char>(Map::FREE):
							PxFreeConuter++;
							break;

						case static_cast<char>(Map::OPSTICAL):
							PxOpsticalConuter++;
							break;

						default:
							std::cout << "Map: CreateGrid: switch default choosen. value= " << PngMap[(i * GridCellSizeInPx + pI) * 4 + (j * GridCellSizeInPx + pJ)* MapWidth * 4] << endl;
						}

					// Debugs
					//std::cout << "cell No': " <<(i * GridCellSizeInPx
					//		+ pI) * 4 + (j * GridCellSizeInPx + pJ)* MapWidth * 4 << std::endl;
				}
			}
			// Chack for number of color cell TODO:think if i need a parameter for Negligible number of blac px
			if (PxGrayCounter >= PxFreeConuter) {
				if (PxGrayCounter > PxOpsticalConuter){
					Grid[i * GridCols + j] = static_cast<char>(Map::GRAY);
				}
				else
					Grid[i * GridCols + j] = static_cast<char>(Map::OPSTICAL);
			} else {
				if (PxFreeConuter > PxOpsticalConuter)
					Grid[i * GridCols + j] = static_cast<char>(Map::FREE);
				else
					Grid[i * GridCols + j] = static_cast<char>(Map::OPSTICAL);
			}
		}

	}

	return Grid;

}

Map::~Map() {
	// TODO: clear all objects!!!!
}

Cell* Map::getCell(int x, int y) const {
	if (x < 0 || y < 0 || x >= this->m_Cols || y >= this->m_Rows) {
		return NULL;
	}
	unsigned int index = y*this->m_Cols + x;
//	return new Cell(
//		(unsigned)x,
//		(unsigned)y,
//		this->Grid[index]
//	);
	return NULL;
}

void Map::PrintMap(const char* filename) {
	unsigned width, height;
	std::vector<unsigned char> Image;

	// sizing
	height = this->getRows();
	width = this->getCols();
	Image.resize(width * height * 4);

	for (unsigned y = 0; y < height; y++)
		for (unsigned x = 0; x < width; x++) {
			// debug
			//cout << "cell : " << y * width + x << " Image Pxs : " << y * width * 4 + x * 4 + 0 << " value : " << this->Grid[y * width + x] * 255 <<endl;
			Image[y * width * 4 + x * 4 + 0] = this->Grid[y * width + x] * 255;
			Image[y * width * 4 + x * 4 + 1] = this->Grid[y * width + x] * 255;
			Image[y * width * 4 + x * 4 + 2] = this->Grid[y * width + x] * 255;
			Image[y * width * 4 + x * 4 + 3] = 255;
		}

	// encode the map
	encodeOneStep(filename, Image, width, height);

	// free memory
	Image.clear();
	vector<unsigned char>().swap(Image);

}

Cell* Map::pointToGrid(unsigned x, unsigned y)
{
	// Get config instance
	ConfigurationManager* config = ConfigurationManager::GetInstance();
	// creat the return cells
	unsigned l1 = floor(this->pngHeight * (unsigned)config->getPixelPerCm()  / config->getPngGridResolution());
	unsigned l2 = floor(this->pngHeight * config->getPixelPerCm() / config->getPngGridResolution());
	return new Cell(l1,l2,(CellType)this->Grid[y * this->m_Cols + x]);
}

