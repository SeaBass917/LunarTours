/******************************************************************************

Vertex.h

Copyright © 2001-2017 Kenneth S. Gregg. All rights reserved.

PLEASE DO NO ALTER THE CONTENTS OF THIS FILE.

*******************************************************************************/

#ifndef VERTEX_H_USED_
#define VERTEX_H_USED_

#include <string>
#include <vector>

using std::string;				// pull in just string from std namespace
using std::vector;				// pull in just vector from std namespace

// A forward reference is required here, because Vertex refers to Edge pointers,
// so the compiler has to be told that Edge is defined as a class.
class Edge;

// This class defines a vertex in the graph, representing a lunar location. Note
// that the constructor receives latitude and longitude in degrees, but they are 
// stored internally in radians. The conversion is performed by the constructor.

class Vertex
{
public:

	Vertex(const string &name, double latitudeDegrees, double longitudeDegrees);

	const string &Name() const;					// read-only access to private member
	double LatitudeRadians() const;				// read-only access to private member
	double LongitudeRadians() const;			// read-only access to private member

private:

	string name;
	double latitudeRadians;
	double longitudeRadians;
	vector<const Edge *> incidentEdges;

	// The following private members are used by the shortest path algorithm.

	void PrepareForShortestPathAlgorithm();
	bool isWhite;
	double shortestPathEstimate;
	Vertex *pParent;

	// We allow Graph to access private members of Vertex.

	friend class Graph;
};

#endif