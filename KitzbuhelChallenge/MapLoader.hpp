#pragma once

#include <iostream>

struct Node
{
	Node()
		: east(nullptr), south(nullptr), west(nullptr), north(nullptr), height(0)
	{

	}

	Node(Node* inEast, Node* inSouth, Node* inWest, Node* inNorth, uint32_t height)
		: east(inEast), south(inSouth), west(inWest), north(inNorth), height(height)
	{
		
	}

	Node* east;
	Node* south;
	Node* west;
	Node* north;
	uint32_t height;
};

class MapLoader
{
public:
	MapLoader()
		: head(new Node())
	{	
		std::cout << "Hello World!\n";
	}

	void LoadMapFile(std::string fileName);

private:
	
	Node* head; //Note: use  head->east as link to the start of the map
	uint32_t dimensionX;
	uint32_t dimensionY;
};