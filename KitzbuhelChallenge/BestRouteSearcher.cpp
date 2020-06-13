#include "BestRouteSearcher.hpp"
#include <queue>

BestRouteSearcher::BestRouteSearcher(std::string fileName)
	: m_mapHead(nullptr)
	, m_currRootNode(nullptr)
	, m_rootNodeOfBest(nullptr)
	, m_tailNodeOfBest(nullptr)
	, m_lengthOfBest(0)
	, m_steepnOfBest(0)
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
		std::cout << "parent recon steepn" << node->search_parent->search_steepn + node->search_parent->height << " own heigh" << node->height << std::endl;
		return (node->search_parent->search_steepn + node->search_parent->height) - node->height;
	}
}

void BestRouteSearcher::UpdateBestRoute(Node* tailNodeCandidateBest, uint32_t const lengthCandidateBest)
{
	//DBUGZ fill up the root of the best if we need to backtrack the parent
	//DBUGZ fill up the steepnOfBest if it is longer than current best
	// Do we even need to save the parent?

	if (nullptr == m_tailNodeOfBest)
	{
		std::cout << "UPDATED NULL Best Length from " << m_lengthOfBest << " to " << lengthCandidateBest << std::endl;
		m_tailNodeOfBest = tailNodeCandidateBest;
		m_lengthOfBest = lengthCandidateBest;

		return;
	}

	if (lengthCandidateBest > m_lengthOfBest)
	{
		std::cout << "UPDATED Best Length from " << m_lengthOfBest << " to " << lengthCandidateBest << std::endl;
		m_tailNodeOfBest = tailNodeCandidateBest;
		m_lengthOfBest = lengthCandidateBest;
	}
	else if (lengthCandidateBest == m_lengthOfBest)
	{
		//DBUGZ now check steepness
		//get parent
		if (tailNodeCandidateBest->search_steepn > m_tailNodeOfBest->search_steepn)
		{
			std::cout << "UPDATED STEEP Best Length from " << m_lengthOfBest << " to " << lengthCandidateBest << std::endl;
			m_tailNodeOfBest = tailNodeCandidateBest;
			m_lengthOfBest = lengthCandidateBest;
		}
	}
}

void BestRouteSearcher::FindBestRouteOfRootNode(Node* rootNode)
{
	//DBUGZ make queue
	std::queue<Node*> searchQueue;

	rootNode->search_length = 1;
	//rootNode->search_parent = nullptr; //DBUGZ just unset it
	searchQueue.push(new Node(*rootNode));

	while (!searchQueue.empty())
	{
		Node* searchSubRootNode = searchQueue.front();

		UpdateBestRoute(searchSubRootNode, searchSubRootNode->search_length);

		std::cout << "PATH: " << searchSubRootNode->height << " PATH LEN: " << searchSubRootNode->search_length << std::endl;

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
	//FindBestRouteOfRootNode(m_mapHead->east); //DBUZG because m_mapHead points to the empty head

	Node* searchRowRoot = m_mapHead->east;
	Node* searchColRoot = searchRowRoot;
	uint32_t dimensionX = m_map.GetDimensionX();
	uint32_t dimensionY = m_map.GetDimensionY();

	for (uint32_t row = 0; row < dimensionY; ++row)
	{

		for (uint32_t col = 0; col < dimensionX; ++col)
		{

			if (searchColRoot->height < m_lengthOfBest)
			{
				std::cout << "ROOT IGNORED" << searchColRoot->height << std::endl;
			}
			else
			{
				std::cout << "ROOT" << searchColRoot->height << std::endl;
				FindBestRouteOfRootNode(searchColRoot);
			}

			searchColRoot = searchColRoot->east;
		}

		searchRowRoot = searchRowRoot->south; //DBUGZ row pointer go southwards
		searchColRoot = searchRowRoot;
	}

	//DBUGZ printing part
	//DBUGZ printing part
	//DBUGZ printing part

	std::cout << "BEST Route length: " << m_tailNodeOfBest->search_length << " STEEPNESS " << m_tailNodeOfBest->search_steepn << std::endl;
	std::cout << "ROUTE: ";

	Node* printPtr = m_tailNodeOfBest;
	while (nullptr != printPtr)
	{
		std::cout << printPtr->height << " ";
		printPtr = printPtr->search_parent;
	}

	//DBUGZ here we check if that searchRootNode is worth checking
	//DBUGZ if the height of the Node is less than the length of the best Route, dont bother checking
}