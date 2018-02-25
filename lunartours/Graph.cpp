//////////////////////////////////////////////////////////////////////////////////////////////////
//
//   Desinger: Sebastian Thiem (A01252370)
//   CRN: 24121
//   Summary: Impliments the Graph methods
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "Graph.h"
#include <sstream>
#include <iostream>
#include <iomanip>


using namespace std;

/***************
Public Methods
***************/

// Oblitorates the graph
Graph::~Graph()
{
	// UploadSecretDocuments(fileName, webAddress, "password1");

	// Clean all the edges
	for (unsigned i = 0; i < edges.size(); i++)
	{
		// Destroy the hardrives because the gov't is on to us
		delete edges[i];
	}
	edges.clear();

	// Clean all the corners
	for (unsigned i = 0; i < vertices.size(); i++)
	{
		// Deleting browser history
		delete vertices[i];
	}
	vertices.clear();
}

// Adds a vertex to the graph
void Graph::AddVertex(const string &name, double latitudeDegrees, double longitudeDegrees)
{
	try
	{
		// Check to see if the vertex is already here(it shouldn't be)
		if (!FindVertexByName(name))
		{
			// Heres where we add the vertex to the verticies vector
			vertices.push_back(new Vertex(name, latitudeDegrees, longitudeDegrees));
		}
		else
		{
			// Tried to add an already present vertex
			throw invalid_argument("   ERROR! Tried to add an already present vertex!");
		}
	}
	catch (exception &ex)
	{
		cout << ex.what() << endl;
	}
}

// Adds an edge to the graph
void Graph::AddEdge(const string &name1, const string &name2)
{
	try
	{
		Vertex* vertex1 = FindVertexByName(name1);
		Vertex* vertex2 = FindVertexByName(name2);

		// Check that they exist
		if (vertex1 && vertex2)
		{
			// Check that these two verticies are not already connected directly
			if (!EdgeExists(vertex1, vertex2))
			{
				// Make a temp var cuz we use it like 3 times, so honestly, thats worth its own variable
				Edge* edge = new Edge(vertex1, vertex2);

				// Add this new edge to the list of edges
				edges.push_back(edge);

				// Update the vertices on what just went down
				vertex1->incidentEdges.push_back(edge);
				vertex2->incidentEdges.push_back(edge);
			}
			else
			{
				// There is alread an edge connecting these two
				throw invalid_argument("   ERROR! User given verticies are already connected!");
			}
		}
		else
		{
			// One of these two vertecies does not exist
			throw invalid_argument("   ERROR! One or both verticies does not exist!");
		}
	}
	catch (exception &ex)
	{
		cout << ex.what() << endl;
	}
}

// Impliments Dijkstra's algorithm and returns a message
string Graph::ShortestPathBetween(const string &name1, const string &name2) const
{
	try
	{
		// Set local vertices based on the names we got
		Vertex* pVertexBeg = FindVertexByName(name1);
		Vertex* pVertexEnd = FindVertexByName(name2);

		// Check that they are even here
		if (pVertexBeg && pVertexEnd)
		{
			// Get each vertex on the graph ready for the awesomeness that is Dijkstra
			for (unsigned i = 0; i < vertices.size(); i++)
			{
				vertices[i]->PrepareForShortestPathAlgorithm();
				/*
					Vertices -> white
					Parent pointers -> NULL
					Shortest path estimates -> infinity
				*/
			}

			// Set a local pointer thats gunna bounce around the graph
			Vertex* pCurrent = pVertexBeg;
			pCurrent->isWhite = false;
			pCurrent->shortestPathEstimate = 0;

			// While pCurrent is pointing somewhere, and that somewhere is not the end
			while (pCurrent && (pCurrent != pVertexEnd))
			{
				RelaxEdgesOnVertex(pCurrent);
				pCurrent = SelectWhiteVertexWithShortestPath();

				if (pCurrent)
				{
					pCurrent->isWhite = false;
				}
			}
			
			// Now to return the results
			if (pCurrent)
			{
				ostringstream sString;

				sString << "Shortest path from " << name1 << " to " << name2 <<
					"\n\n   Distance = " << fixed << setprecision(6) << pVertexEnd->shortestPathEstimate << " km\n\n";
				
				// pCurrent is being repurposed here
				pCurrent = pVertexEnd;

				// Temp vector cuz we wanna display from beg to end
				vector<string> vStrings;

				// adds the destination to the vector
				vStrings.push_back(pCurrent->name);

				// While the parent pointers are non-NULL
				while (pCurrent->pParent)
				{
					vStrings.push_back(pCurrent->name);	// Add to the temp vector

					pCurrent = pCurrent->pParent;	// Move forward
				}

				// adds the start to the vector
				vStrings.push_back(pCurrent->name);

				// Heres where we get them in the order we want
				for (unsigned i = vStrings.size() - 1; i > 0; --i)
				{
					sString << "      " << vStrings[i] << "\n";
				}

				return sString.str();
			}
			else
			{
				// Shortest path was not found
				return "";	// Empty String
			}
		}
		else
		{
			// The names we got dont match anything on the graph
			throw invalid_argument("   ERROR! One or both verticies does not exist!");
		}
	}
	catch (exception &ex)
	{
		cout << ex.what() << endl;
		return "";
	}
}

/***************
Private Methods
***************/

// Searches the graph for the inputed name
Vertex* Graph::FindVertexByName(const string &name) const
{
	for (unsigned i = 0; i < vertices.size(); i++)
	{
		// Checks if the name were looking for is here
		if (vertices[i]->name == name)
		{
			// Returns a pointer to the vertex is i has the same name
			return vertices[i];
		}
	}

	// Null on failure
	return NULL;
}

// Tries to find an edge that contains these two vertices, true if one exists
bool Graph::EdgeExists(const Vertex *pVertex1, const Vertex *pVertex2) const
{
	for (unsigned i = 0; i < edges.size(); i++)
	{
		// Returns true if the verticies given match the verticies on an edge
		if (pVertex1 == edges[i]->Vertex1() && pVertex2 == edges[i]->Vertex2())
		{
			return true;
		}

		// Will still return true if the vertices were given backwards
		if (pVertex1 == edges[i]->Vertex2() && pVertex2 == edges[i]->Vertex1())
		{
			return true;
		}
	}

	return false;
}

// Goes through the incident edges and updates the shortest path for the neighbour vertices
void Graph::RelaxEdgesOnVertex(Vertex *pVertex) const
{
	// Local pointer that will point to the vertex at the other end of each edge
	Vertex* pNeighbourVertex; 

	// Loops through all the vertex's incident edges
	for (unsigned i = 0; i < pVertex->incidentEdges.size(); i++)
	{
		// Makes sure we are pointing to the neighbour and not the current vertex
		if (pVertex->incidentEdges[i]->Vertex1() == pVertex)
		{
			pNeighbourVertex = pVertex->incidentEdges[i]->Vertex2();
		}
		else
		{
			pNeighbourVertex = pVertex->incidentEdges[i]->Vertex1();
		}

		// If the neighbour is white
		if (pNeighbourVertex->isWhite)
		{
			// Comput the sum of current shortestpathest and the weight across the edge
			double weightSum = pVertex->shortestPathEstimate + pVertex->incidentEdges[i]->Weight();
			
			// If that sum is equal to or smaller than the neightbour update the neighbour
			if (weightSum <= pNeighbourVertex->shortestPathEstimate)
			{
				pNeighbourVertex->shortestPathEstimate = weightSum;

				pNeighbourVertex->pParent = pVertex;
			}
		}
	}
}

// 
Vertex* Graph::SelectWhiteVertexWithShortestPath(void) const
{
	// A pointer to hold the shortest vertex we find
	Vertex* pNext = NULL;

	// A double to hold the shortest path estimate we find
	double minShortPathEst = numeric_limits<double>::infinity();

	// Looks for a path that is open and the shortest
	for (unsigned i = 0; i < vertices.size(); i++)
	{
		if (vertices[i]->isWhite && vertices[i]->shortestPathEstimate < minShortPathEst)
		{
			// Updates our locals on whos the shortest
			pNext = vertices[i];
			minShortPathEst = vertices[i]->shortestPathEstimate;
		}
	}

	// Note: will returns null if no shortest neighbours exist
	return pNext;
}