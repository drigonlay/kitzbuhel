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

	std::string line;
	uint32_t val;

	// Part 1: Get dimensions
	if (std::getline(inFile, line))
	{
		std::istringstream iss(line);
		iss >> dimensionX >> dimensionY;
	}

	// Part 2: Create map
	Node* currNode = head;
	Node* prevRowStart = head;
	Node* prevNode = nullptr;

	for (uint32_t row = 0; row < dimensionY; ++row)
	{
		if (std::getline(inFile, line))
		{
			std::istringstream iss(line);

			for (uint32_t col = 0; col < dimensionX; ++col)
			{
				iss >> val;

				if (0 == row)
				{
					Node* temp = new Node();
					temp->height = val;
					temp->west = &(*currNode);	//DBUGZ point back to previous
					currNode->east = temp;		//DBUGZ point to forward
					currNode = temp;			//DBUZG move curPtr new Node

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


						Node* temp = new Node();
						temp->height = val;
						temp->north = prevNode;
						prevNode->south = temp;
						//temp->west  //DBUGZ this is null
						//temp->east  //DBUGZ this is null

						currNode = temp;
						prevNode = prevNode->east;
					}
					else
					{
						Node* temp = new Node();
						temp->height = val;
						temp->north = &(*prevNode);		//DBUGZ point back to northern previous
						temp->west = &(*currNode);		//DBUGZ this will be pointing to null if first column
						
						currNode->east = temp;
						prevNode->south = temp;

						currNode = currNode->east;
						prevNode = prevNode->east;
					}
				}
			}

		}

		if (0 != row)
		{
			prevRowStart = prevRowStart->south;
		}
	} //end for (uint32_t row = 0; row < dimensionY; ++row)

	inFile.close();
}

void MapLoader::PrintMap() //DBUGZ for debugging
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