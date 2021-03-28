#include <iostream>
#include <utility>
#include "dijkstra.h"
#include "heap.h"
#include "wdigraph.h"

/* Dijkstra's algorithm finds the path of least cost for all points
 * in a graph given a starting vertex.
 * Arguments: 
 * 	graph (const WDigraph&): a weighted directed graph with 
 * 				vertices, edges and their assiciated
 * 				costs.
 * 	startVertex (int): the vertex ID for the starting vertex
 * 	tree (unordered_map<int, PIL>&): an empty search tree that is 
 * 				passed in, and will be populated by 
 * 				this function. This tree will have 
 * 				the key as an arbitrary point, and the item
 * 				will be a pair<int, long long> of 
 * 				<preceding point, total cost>.
 *
 * */
void dijkstra(const WDigraph& graph, int startVertex, 
			  unordered_map<int, PIL>& tree) {
	
	// <previousVertex, currentVertex>, current_cost
	// the most uncreative name given for the heap.
	BinaryHeap<pair<int, int>, long long> heep;
	// inserts the first vertex
	heep.insert({startVertex, startVertex}, 0);

    	while (heep.size() > 0) {
		HeapItem<pair<int, int> , long long> node = heep.min();
		int u = node.item.first;
		int v = node.item.second;
		long long this_cost = node.key;
		
		// if the node has not been searched before, put it in 
		// the search tree, and put neighbours in heap
		if (!(tree.find(v) != tree.end()))
		{	
			tree[v] = {u, this_cost};
			for (auto it = graph.neighbours(v); it != graph.endIterator(v); it++)
			{	
				// cost is the total cost + cost of the new edge
				long long cost = this_cost + graph.getCost(v, *it);
				heep.insert({v,*it}, cost);
			}
		}	

		// remove top item
		heep.popMin();
    	} 

}
