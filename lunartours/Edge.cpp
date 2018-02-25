//////////////////////////////////////////////////////////////////////////////////////////////////
//
//   Desinger: Sebastian Thiem (A01252370)
//   CRN: 24121
//   Summary: Impliments the Edge methods
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include <cmath> 
#include "Edge.h"
#include <iostream>

using namespace std;

/***************
Public Methods
***************/

Edge::Edge(Vertex *pVertex1, Vertex *pVertex2)
{
	try
	{
		if (pVertex1)
		{
			// pVertex1 is okilie dokilie
			if (pVertex2)
			{
				// pVertex2 is okilie dokilie

				// Initializes the verteciis to the input verteciiiiiii
				this->pVertex1 = pVertex1;
				this->pVertex2 = pVertex2;

				// Calculates the weight using the haversine formula
				this->weight = 2 * 1737.10 * asin(sqrt(pow(sin((pVertex2->LatitudeRadians() - pVertex1->LatitudeRadians()) / 2), 2) + cos(pVertex1->LatitudeRadians()) * cos(pVertex2->LatitudeRadians()) * (pow(sin((pVertex2->LongitudeRadians() - pVertex1->LongitudeRadians()) / 2), 2))));

			}
			else
			{
				//pVertex2 is null
				throw invalid_argument("   ERROR! pVertex2 is null");
			}
		}
		else
		{
			//pVertex1 is null
			throw invalid_argument("   ERROR! pVertex1 is null");
		}
	}
	catch (exception &ex)
	{
		cout << ex.what() << endl;
	}
}

Vertex* Edge::Vertex1() const
{
	return this->pVertex1;
}

Vertex* Edge::Vertex2() const
{
	return this->pVertex2;
}

double Edge::Weight() const
{
	return this->weight;
}