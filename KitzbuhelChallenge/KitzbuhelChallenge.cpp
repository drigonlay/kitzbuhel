// KitzbuhelChallenge.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "BestRouteSearcher.hpp"

int main()
{
    BestRouteSearcher searcher("mapsmall.txt");

    searcher.PrintMap();
    searcher.FindBestRouteOfMap();

    //MapLoader* map = new MapLoader();
    //map->LoadMapFile("mapsmall.txt");

    /*
        Algorithm 1 - Dirty brute force, breadth first search
            
           1. Load map into linked list grid.
           2. Start from first search root node, moving eastward and then southward
           3. Perform breadth first search, priorty of direction is east>south>weast>north.
                Note: When doing BFS, calculate the steepness - take care of the route back later

                Push current visited nodes into Route
                    Route - contains a stack of the visited nodes to backtrack the route
                                     - contains the length of the route
                                     - contains the difference between root node and last node

                If the Route is longer and then steeper than current best Route - replace the best Route with the new Route

                If searcher reaches a dead end, go back to #2

            4. If currentRootNode < (bestStartNode - bestEndNode)

                400 < (1500 - 700)
                400 < 800

        Algorithm 1 - Dirty brute force,  first search

        Algorithm - Optimized:

           1. Load map into linked list grid. 
                // Save the node of the highest value and the node of the lowest value. -- Not gonna work, there are duplicates

           2. 
    */
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
