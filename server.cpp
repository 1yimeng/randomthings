#include <string>
#include <iostream>
#include <unordered_map>
#include <cmath>
#include <fstream>
#include <algorithm>
#include <vector>
#include "wdigraph.h"
#include "digraph.h"
#include "heap.h"
#include "dijkstra.h"
using namespace std;

struct Point {
	long long lat;
	long long lon;
};

long long mahanttan(const Point& pt1, const Point& pt2) {
	// Return the Manhattan distance between the two given points
	long long distance = abs(pt1.lon - pt2.lon) + abs(pt1.lat - pt2.lat);
	return distance;
}

void readGraph(string filename, WDigraph& graph, unordered_map<int, Point>& points) {
	/*
	Read the Edmonton map data from the provided file
	and load it into the given WDigraph object.
	Store vertex coordinates in Point struct and map
	each vertex to its corresponding Point struct.
	PARAMETERS:
	filename: name of the file describing a road network
	graph: an instance of the weighted directed graph (WDigraph) class
	points: a mapping between vertex identifiers and their coordinates
	*/
	ifstream myfile;
	myfile.open(filename);
	string newthing;
	int avertex;
	int vertex1;
	int vertex2;
	int second = 0;
	int third = 0;
	double lat;
	double lon;
	long long latlong;
	long long lonlong;
	Point mypoint;

	while (getline(myfile, newthing)) {
		// finding the positions of commas for input
		second = newthing.find(",", 2);
		third = newthing.find(",", second + 1);
		
		// add vertices or edge to Digraph depending on the input
		if (newthing[0] == 'V') {
			
			avertex = stoi(newthing.substr(2, second - 2));
			lat = stod(newthing.substr(second + 1, third - second - 1));
			lon = stod(newthing.substr(third+1, newthing.size()-1));
			graph.addVertex(avertex);
			latlong = static_cast <long long> (lat * 100000);
			lonlong = static_cast <long long> (lon * 100000);
			mypoint.lat = latlong;
			mypoint.lon = lonlong;
			points[avertex] = mypoint;

		} else if (newthing[0] == 'E') {
			
			vertex1 = stoi(newthing.substr(2, second - 2));
			vertex2 = stoi(newthing.substr(second + 1, third - second - 1));
			graph.addEdge(vertex1, vertex2, mahanttan(points[vertex1],points[vertex2]));

		}
	}
	myfile.close();
}

vector<Point> pathFind(int start, int end, 
		unordered_map<int, pair<int, long long> >& tree,
		unordered_map<int, Point>& points)
{
	vector<Point> path = {points[end]};
	int curr_vertex = end;
	while (curr_vertex != start)
	{	
		path.push_back(points[tree[curr_vertex].first]);
		curr_vertex = tree[curr_vertex].first;
	}
	reverse(path.begin(), path.end());
	return path;
}












int main()
{
	WDigraph graph;
	unordered_map<int, Point> points;
	string filename = "custom-tests/test1";
	readGraph(filename, graph, points);
	unordered_map<int, pair<int, long long> > tree;


	dijkstra(graph, 1, tree);
	for (auto x: tree)
	{
		cout << x.first << ", " << x.second.first << ", " << x.second.second << endl;
	}
	cout << graph.size() << endl;

	vector<Point> somepath = pathFind(1, 6, tree, points); 
	for (int i = 0; i < somepath.size(); i++)
	{
		cout << somepath[i].lat/100000 << ", " << somepath[i].lon/100000 << endl;
	}
	return 0;
}
