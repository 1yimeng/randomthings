#include <string>
#include <iostream>
#include <unordered_map>
#include <cmath>
#include <fstream>
#include "wdigraph.h"
#include "digraph.h"
#include "heap.h"
#include "dijkstra.h"
#include <vector>
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

vector<int> getidentifier(const unordered_map<int, Point>& points) {
	int lat1, lon1, lat2, lon2;
	cin >> lat1 >> lon1 >> lat2 >> lon2;
	Point point1;
	Point point2;
	point1.lat = lat1;
	point1.lon = lon1;
	point2.lat = lat2;
	point2.lon = lon2;
	int identifier1, identifier2;
	bool result = false;
	vector<int> twoidentifiers;
	auto it = points.begin();
	while (it != points.end()) {

		if (it->second == point1) {
			identifier1 = it->first;
		}

		if (it->second == point2) {
			identifier2 = it->first;
		}

		it++;
	}
	twoidentifiers.push_back(identifier1);
	twoidentifiers.push_back(identifier2);
	return twoidentifiers;
}

int main()
{
	WDigraph graph;
	unordered_map<int, Point> points;
	string filename = "edmonton-roads-2.0.1.txt";
	readGraph(filename, graph, points);
	unordered_map<int, pair<int, long long> > tree;
<<<<<<< HEAD
	dijkstra(graph, 1, tree);
	for (auto x: tree)
	{
		cout << x.first << ", " << x.second.first << ", " << x.second.second << endl;
	}
=======


	//dijkstra(graph, 1, tree);
	//for (auto x: tree)
	//{
		//cout << x.first << ", " << x.second.first << ", " << x.second.second << endl;
	//}
>>>>>>> 01011b24f142da4e2b0904ef955c3fd3711c1738
	cout << graph.size() << endl;

	return 0;
}
