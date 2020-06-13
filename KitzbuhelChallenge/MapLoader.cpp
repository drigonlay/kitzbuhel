#include "MapLoader.hpp"
#include <fstream>
#include <string>
#include <sstream>

void MapLoader::LoadMapFile(std::string fileName)
{
	std::ifstream inFile;

	inFile.open(fileName);
	
	if (!inFile)
	{
		std::cout << "File does not exist!" << std::endl;
		exit(1);
	}

	std::cout << "Loading map..." << std::endl;

	std::string line;

	if (std::getline(inFile, line))
	{
		std::istringstream iss(line);
		iss >> dimensionX >> dimensionY;
	}

	std::cout << "Map size " << dimensionX << " x " << dimensionY << std::endl;

	Node* currNode = head;
	Node* prevRowStart = head;
	Node* prevNode = nullptr;

	uint32_t val;

	for (uint32_t row = 0; row < dimensionY; ++row)
	{
		if (std::getline(inFile, line))
		{
			std::istringstream iss(line);

			for (uint32_t col = 0; col < dimensionX; ++col)
			{
				iss >> val;

				Node* temp = new Node();
				temp->height = val;

				if (0 == row)
				{
					temp->west = currNode;
					currNode->east = temp;
					currNode = temp;

					if (0 == col)
					{
						prevRowStart = head->east;
					}
				}
				else
				{
					if (0 == col)
					{
						prevNode = prevRowStart;
						currNode = temp;
					}
					else
					{
						temp->west = currNode;
						currNode->east = temp;
						currNode = currNode->east;
					}

					temp->north = prevNode;
					prevNode->south = temp;
					prevNode = prevNode->east;
				}
			}
		}

		if (0 != row)
		{
			prevRowStart = prevRowStart->south;
		}
	}

	inFile.close();
}

void MapLoader::PrintMap()
{
	std::cout << "Rows: " << dimensionX << " Cols: " << dimensionY << std::endl;

	Node* printRowHead = head->east;

	for (uint32_t row = 0; row < dimensionY; ++row)
	{
		Node* printPtr = printRowHead;

		for (uint32_t col = 0; col < dimensionX; ++col)
		{
			std::cout << printPtr->height << " ";
			printPtr = printPtr->east;
		}

		std::cout << std::endl;

		printRowHead = printRowHead->south;
	}
}