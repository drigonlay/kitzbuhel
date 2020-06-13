#pragma once

#include <iostream>
#include "MapLoader.hpp"

class BestRouteSearcher
{
public:

	BestRouteSearcher(std::string fileName);

	void LoadMapAndGetMapHead(std::string fileName);

	void PrintMap();

	void FindBestRouteOfRootNode(Node* rootNode);

	void FindBestRouteOfMap();

private:

	void UpdateBestRoute(Node* tailNodeOfBest, uint32_t lengthOfBest); //DBUGZ later find out how to  reconstruct the route node by node

	uint32_t CalcSteepn(Node* node);

	MapLoader m_map;
	Node* m_mapHead;
	Node* m_currRootNode;

	Node* m_rootNodeOfBest;
	Node* m_tailNodeOfBest;
	uint32_t m_lengthOfBest;
	uint32_t m_steepnOfBest;
};