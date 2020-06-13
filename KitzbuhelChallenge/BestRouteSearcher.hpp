#pragma once

#include <iostream>
#include "MapLoader.hpp"

class BestRouteSearcher
{
public:

	BestRouteSearcher(std::string fileName);

	void PrintMap();

	void FindBestRouteOfMap();

	void PrintBestRoute();

private:

	void UpdateBestRoute(Node* tailNodeOfBest, uint32_t lengthOfBest);

	uint32_t CalcSteepn(Node* node);

	void FindBestRouteOfRootNode(Node* rootNode);

	void LoadMapAndGetMapHead(std::string fileName);

	MapLoader m_map;
	Node* m_mapHead;
	Node* m_tailNodeOfBest;
};