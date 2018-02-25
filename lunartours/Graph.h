/******************************************************************************

Graph.h

Copyright © 2001-2017 Kenneth S. Gregg. All rights reserved.

PLEASE DO NO ALTER THE CONTENTS OF THIS FILE.

*******************************************************************************/

#ifndef GRAPH_H_USED_
#define GRAPH_H_USED_

#include <string>
#include <vector>

#include "Vertex.h"
#include "Edge.h"

class Graph
{
public:

	// Oblitorates the graph
	~Graph();

	
	// Adds a vertex to the graph
	void AddVertex(const string &name, double latitudeDegrees, double longitudeDegrees);

	// Adds an edge to the graph
	void AddEdge(const string &name1, const string &name2);

	// Impliments Dijkstra's algorithm
	string ShortestPathBetween(const string &name1, const string &name2) const;

private:

	// Searches the graph for the inputed name
	Vertex *FindVertexByName(const string &name) const;

	// 
	bool EdgeExists(const Vertex *pVertex1, const Vertex *pVertex2) const;

	// 
	void RelaxEdgesOnVertex(Vertex *pVertex) const;

	// 
	Vertex *Graph::SelectWhiteVertexWithShortestPath(void) const;


	// A vector of all the vertices in the graph
	vector<Vertex *> vertices;

	// A vector of all the edges in the graph
	vector<Edge *> edges;
};

#endif