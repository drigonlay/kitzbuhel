#include "BestRouteSearcher.hpp"
#include <queue>
#include <string>

BestRouteSearcher::BestRouteSearcher(std::string fileName)
	: m_mapHead(nullptr)
	, m_tailNodeOfBest(nullptr)
{
	LoadMapAndGetMapHead(fileName);
}

void BestRouteSearcher::LoadMapAndGetMapHead(std::string fileName)
{
	m_map.LoadMapFile(fileName);
	m_mapHead = m_map.GetMapHead();
}

void BestRouteSearcher::PrintMap()
{
	m_map.PrintMap();
}

uint32_t BestRouteSearcher::CalcSteepn(Node* node)
{
	if (nullptr == node->search_parent)
	{
		return 0;
	}
	else
	{
		return (node->search_parent->search_steepn + node->search_parent->height) - node->height;
	}
}

void BestRouteSearcher::UpdateBestRoute(Node* tailNodeCandidateBest, uint32_t const lengthCandidateBest)
{
	if (nullptr == m_tailNodeOfBest)
	{
		m_tailNodeOfBest = tailNodeCandidateBest;
		return;
	}

	if (tailNodeCandidateBest->search_length > m_tailNodeOfBest->search_length)
	{
		m_tailNodeOfBest = tailNodeCandidateBest;
	}
	else if (tailNodeCandidateBest->search_length == m_tailNodeOfBest->search_length)
	{
		if (tailNodeCandidateBest->search_steepn > m_tailNodeOfBest->search_steepn)
		{
			m_tailNodeOfBest = tailNodeCandidateBest;
		}
	}
}

void BestRouteSearcher::FindBestRouteOfRootNode(Node* rootNode)
{
	std::queue<Node*> searchQueue;

	rootNode->search_length = 1;
	searchQueue.push(new Node(*rootNode));

	while (!searchQueue.empty())
	{
		Node* searchSubRootNode = searchQueue.front();

		UpdateBestRoute(searchSubRootNode, searchSubRootNode->search_length);

		//DBUGZ NOTE so you stop thinking about this. It is impossible for a Node to 
		//push its parent into the stack because it will always have a lesser height than its parent
		//DBUGZ NOTE search also checks the empty head since it is west of map Root Node

		//DBUGZ search east
		if (nullptr != searchSubRootNode->east)
		{
			if (searchSubRootNode->height > searchSubRootNode->east->height)
			{
				Node* temp = new Node(*searchSubRootNode->east);
				temp->search_parent = searchSubRootNode;
				temp->search_length = searchSubRootNode->search_length + 1;
				temp->search_steepn = CalcSteepn(temp);
				searchQueue.push(temp);
			}
		}

		//DBUGZ search south
		if (nullptr != searchSubRootNode->south)
		{
			if (searchSubRootNode->height > searchSubRootNode->south->height)
			{
				Node* temp = new Node(*searchSubRootNode->south);
				temp->search_parent = searchSubRootNode;
				temp->search_length = searchSubRootNode->search_length + 1;
				temp->search_steepn = CalcSteepn(temp);
				searchQueue.push(temp);
			}
		}

		//DBUGZ search west
		if (nullptr != searchSubRootNode->west)
		{
			if (searchSubRootNode->height > searchSubRootNode->west->height)
			{
				Node* temp = new Node(*searchSubRootNode->west);
				temp->search_parent = searchSubRootNode;
				temp->search_length = searchSubRootNode->search_length + 1;
				temp->search_steepn = CalcSteepn(temp);
				searchQueue.push(temp);
			}
		}

		//DBUGZ search north
		if (nullptr != searchSubRootNode->north)
		{
			if (searchSubRootNode->height > searchSubRootNode->north->height)
			{
				Node* temp = new Node(*searchSubRootNode->north);
				temp->search_parent = searchSubRootNode;
				temp->search_length = searchSubRootNode->search_length + 1;
				temp->search_steepn = CalcSteepn(temp);
				searchQueue.push(temp);
			}
		}

		//DBUGZ fix all these copypasta later

		searchQueue.pop();
	}
}

void BestRouteSearcher::FindBestRouteOfMap()
{
	std::cout << "\nFinding best route ..." << std::endl;

	Node* searchRowRoot = m_mapHead->east;
	Node* searchColRoot = searchRowRoot;
	uint32_t dimensionX = m_map.GetDimensionX();
	uint32_t dimensionY = m_map.GetDimensionY();

	for (uint32_t row = 0; row < dimensionY; ++row)
	{
		for (uint32_t col = 0; col < dimensionX; ++col)
		{
			//DBUGZ here we check if that searchRootNode is worth checking
			//DBUGZ if the height of the Node is less than the length of the best Route, dont bother checking
			if (searchColRoot->height > (nullptr == m_tailNodeOfBest ? 0 : m_tailNodeOfBest->search_length))
			{
				FindBestRouteOfRootNode(searchColRoot);
			}

			searchColRoot = searchColRoot->east;
		}

		searchRowRoot = searchRowRoot->south; //DBUGZ row pointer go southwards
		searchColRoot = searchRowRoot;
	}

	PrintBestRoute();
}

void BestRouteSearcher::PrintBestRoute()
{
	std::cout << "BEST Route length: " << m_tailNodeOfBest->search_length << " STEEPNESS " << m_tailNodeOfBest->search_steepn << std::endl;
	std::cout << "ROUTE: ";

	Node* printPtr = m_tailNodeOfBest;
	std::string routeString;

	while (nullptr != printPtr)
	{
		routeString.insert(0, " ");
		routeString.insert(0, std::to_string(printPtr->height));

		printPtr = printPtr->search_parent;
	}

	std::cout << "RESULT " << routeString << std::endl;
}