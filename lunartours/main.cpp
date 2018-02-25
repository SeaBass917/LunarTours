//////////////////////////////////////////////////////////////////////////////////////////////////
//
//   Desinger: Sebastian Thiem (A01252370)
//   CRN: 24121
//   Summary: Reads the data from the lunar files and finds requested shortest paths
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <cctype>
#include "Graph.h"

using namespace std;

// Checks that the file matches extention parameter case insensative
bool IsExt(const string fileName, string ext)
{
	string fileExt = fileName.substr(fileName.find_last_of(".") + 1);	// Pulling out the extention
	
	// Note: does not jpeg == jpg, consider add that feature
	if (fileExt == ext)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int main(int argc, char *argv[])
{
	// Check that there are enough args
	if (argc == 5)
	{
		// Checks that the args are of the correct extention type
		if (IsExt(argv[1], "txt") &&
			IsExt(argv[2], "txt") &&
			IsExt(argv[3], "txt") &&
			IsExt(argv[4], "txt"))
		{
			// Defines a local graph
			Graph *myGraph = new Graph;

			/********************************************
				Collecting Lunar site data (Vertices)
			********************************************/

			ifstream lunarsites(argv[1]);
			
			if (!lunarsites.fail())
			{
				// Local vars to hold the file data
				string siteName;
				double latitudeAngle;
				char latitudeDirection;
				double longitudeAngle;
				char longitudeDirection;

				while (lunarsites >> siteName
					>> latitudeAngle >> latitudeDirection
					>> longitudeAngle >> longitudeDirection)
				{
					if (latitudeDirection == 'S')
					{
						latitudeAngle *= -1;
					}

					if (longitudeDirection == 'W')
					{
						longitudeAngle *= -1;
					}

					myGraph->AddVertex(siteName, latitudeAngle, longitudeAngle);
				}

				lunarsites.close();

				/******************************************
					Collecting connections data (Edges)
					******************************************/

				ifstream siteconnections(argv[2]);

				if (!siteconnections.fail())
				{
					string name1;
					string name2;

					while (siteconnections >> name1 >> name2)
					{
						myGraph->AddEdge(name1, name2);
					}

					siteconnections.close();

					/*******************************************************************
						Reading the requested paths and outputing the path estimate
					*******************************************************************/

					ifstream requestedtours(argv[3]);
					ofstream output(argv[4]);

					if (!requestedtours.fail())
					{
						if (!output.fail())
						{
							string shortestPathEstimate;
							string start;
							string destination;

							while (requestedtours >> start >> destination)
							{
								shortestPathEstimate = myGraph->ShortestPathBetween(start, destination);
								
								if (!shortestPathEstimate.empty())
								{
									output << shortestPathEstimate;
								}
								else
								{
									output << "There is no path from " << start << " to " << destination << ".";
								}

								output << endl << "----------------------------------------------------------------------"
									<< endl;
							}

							requestedtours.close();
							output.close();

							return 0;
						}
						else
						{
							// output failed

						}
					}
					else
					{
						// requested tours failed

					}
				}
				else
				{
					// site connections failed

				}
			}
			else
			{
				// lunar sites failed to open

			}
		}
		else
		{
			// One or more args was the wrong ext type
			cout << "   ERROR! Files need to be of type: .txt" << endl;
			return -1;
		}
	}
	else
	{
		// Insufficient args
		cout << "   ERROR! Missing " << (5 - argc) << " command-line arguements!" << endl;
		return -1;
	}
}