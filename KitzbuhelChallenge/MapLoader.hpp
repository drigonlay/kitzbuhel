#pragma once

#include <iostream>

struct Node
{
	Node()
		: east(nullptr)
		, south(nullptr)
		, west(nullptr)
		, north(nullptr)
		, height(0)
		, search_parent(nullptr)
		, search_length(0)
		, search_steepn(0)
	{
	}

	Node(const Node& node)
	{
		east = node.east;
		south = node.south;
		west = node.west;
		north = node.north;
		height = node.height;

		search_length = node.search_length;
		search_parent = node.search_parent;
		search_steepn = node.search_steepn;
	}

	Node* east;
	Node* south;
	Node* west;
	Node* north;
	uint32_t height;

	//For search purposes
	Node* search_parent;
	uint32_t search_length;
	uint32_t search_steepn;
};

class MapLoader
{
public:
	MapLoader()
		: head(new Node())
		, dimensionX(0)
		, dimensionY(0)
	{	
	}

	void LoadMapFile(std::string fileName);

	void PrintMap();

	Node* GetMapHead() { return head; }

	uint32_t GetDimensionX() { return dimensionX; }

	uint32_t GetDimensionY() { return dimensionY; }

private:
	
	Node* head; //Note: use  head->east as link to the start of the map
	uint32_t dimensionX;
	uint32_t dimensionY;
};