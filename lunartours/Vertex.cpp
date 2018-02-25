//////////////////////////////////////////////////////////////////////////////////////////////////
//
//   Desinger: Sebastian Thiem (A01252370)
//   CRN: 24121
//   Summary: Impliments the Vertex methods
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#define _USE_MATH_DEFINES 
#include <cmath>
#include <limits>
#include <iostream>
#include "Vertex.h"

using namespace std;

/***************
Public Methods
***************/


Vertex::Vertex(const string &name, double latitudeDegrees, double longitudeDegrees)
{
	try
	{
		// Name is non-empty
		if (!name.empty())
		{
			// Latitude is fine
			if (latitudeDegrees <= 90 && latitudeDegrees >= -90)
			{
				// Longitude is fine
				if (longitudeDegrees <= 180 && longitudeDegrees >= -180)
				{
					// Initialize based on input
					this->name = name;
					this->latitudeRadians = (latitudeDegrees * M_PI) / 180;
					this->longitudeRadians = (longitudeDegrees * M_PI) / 180;

					// initializes the rest of the privates
					PrepareForShortestPathAlgorithm();
				}
				else
				{
					// LongAngle is abnormal
					throw invalid_argument("   ERROR! Invalid angle for longitude!\n");
				}
			}
			else
			{
				// LatAngle is abnormal
				throw invalid_argument("   ERROR! Invalid angle for latitude!\n");
			}
		}
		else
		{
			// Name is empty
			throw invalid_argument("   ERROR! Name is empty!\n");
		}
	}
	catch (exception &ex)
	{
		cout << ex.what() << endl;
	}
}

const string& Vertex::Name() const
{
	return this->name;
}

double Vertex::LatitudeRadians() const
{
	return this->latitudeRadians;
}

double Vertex::LongitudeRadians() const
{
	return this->longitudeRadians;
}

/***************
Private Methods
***************/

void Vertex::PrepareForShortestPathAlgorithm()
{
	// Infinityyyy
	shortestPathEstimate = numeric_limits<double>::infinity();

	isWhite = true;
	pParent = NULL;
}







