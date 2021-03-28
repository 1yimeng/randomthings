#include <iostream>
#include <utility>
#include "dijkstra.h"
#include "heap.h"
#include "wdigraph.h"

void dijkstra(const WDigraph& graph, int startVertex, 
			  unordered_map<int, PIL>& tree) {
	/*
	Compute least cost paths that start from a given vertex.
	Use a binary heap to efficiently retrieve an unexplored vertex that
	has the minimum distance from the start vertex at every iteration.
	PIL is an alias for "pair<int, long long>" type as discussed in class
	PARAMETERS:
	WDigraph: an instance of the weighted directed graph (WDigraph) class
	startVertex: a vertex in this graph which serves as the root of the search tree
	tree: a search tree used to construct the least cost path to some vertex
	*/
	// All active fires stored as follows:
    // say an entry is (v, (u, d)), then there is a fire that started at u
    // and will burn the u->v edge, reaching v at time d
    //list<PIPIL> fires;
	BinaryHeap<pair<int, int>, long long> heep;
	
    // at time 0, the startVertex burns, we use -1 to indicate there is
    // no "predecessor" of the startVertex
    //fireheap.insert(PIPIL(startVertex, PIL(-1, 0)));
	heep.insert({startVertex, startVertex}, 0);
    // while there is an active fire
    int prev = startVertex;
    while (heep.size() > 0) {
	HeapItem<pair<int, int> , long long> node = heep.min();
	int u = node.item.first;
	int v = node.item.second;
	long long this_cost = node.key;
		
	if (!(tree.find(v) != tree.end()))
	{
		tree[v] = {u, this_cost};
		for (auto it = graph.neighbours(v); it != graph.endIterator(v); it++)
		{	
			long long cost = this_cost + graph.getCost(v, *it);
			heep.insert({v,*it}, cost);
		}
	}	
        // auto earliestFire = fires.begin();
        // for (auto iter = fires.begin(); iter != fires.end(); ++iter) {
        //     if (iter->second.second < earliestFire->second.second) {
        //         earliestFire = iter;
        //     }
        // }

        // to reduce notation in the code below, this u,v,d agrees with
        // the intuition presented in the comment when PIPIL is typedef'ed
        //int v = earliestFire->first, u = earliestFire->second.first, d = earliestFire->second.second;

        // remove this fire
        //fires.erase(earliestFire);

		heep.popMin();
    } 

}
