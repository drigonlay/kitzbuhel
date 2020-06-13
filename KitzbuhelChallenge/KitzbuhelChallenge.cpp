#include <iostream>
#include "BestRouteSearcher.hpp"

int main()
{
    BestRouteSearcher searcher2("mapsmall.txt");
    searcher2.FindBestRouteOfMap();

    BestRouteSearcher searcher("map.txt");
    searcher.FindBestRouteOfMap();
}