/*
	HAPI Start
	----------
	This solution contains an already set up HAPI project and this main file
	
	The directory structure and main files are:

	HAPI_Start - contains the Visual Studio solution file (.sln)
		HAPI_Start - contains the Visual Studio HAPI_APP project file (.vcxproj) and source code
			HAPI - the directory with all the HAPI library files
			Data - a place to put your data files with a few sample ones provided

	Additionally in the top directory there is a batch file for creating a redistributable Demo folder

	For help using HAPI:
	https://scm-intranet.tees.ac.uk/users/u0018197/hapi.html
*/

// Include the HAPI header to get access to all of HAPIs interfaces
#include <HAPI_lib.h>

// HAPI itself is wrapped in the HAPISPACE namespace
using namespace HAPISPACE;

// Every HAPI program has a HAPI_Main as an entry point
// When this function exits the program will close down
//-----------------------------------------------------
void ClearToColour(BYTE* screen, const int& screenWidth, const int& screenHeight, const HAPI_TColour& argColour);
//-----------------------------------------------------

void HAPI_Main()
{
	struct Scoordinates3D
	{
		int x;
		int y;
		int z;
		int starSize;
	};	
	//-------------------------------
	const int kNumStars(5000);
	int screenWidth(1024);
	int screenHeight(768);
	int eyeDistance(100);
	int CentreX(1024 / 2);
	int CentreY(768 / 2);
	HAPI_TColour starColour;
	//-------------------------------

	//Initialise the stars
	Scoordinates3D starCoor[kNumStars];
	for (int i = 0; i < kNumStars; i++)
	{
		starCoor[i].x = rand() % screenWidth;
		starCoor[i].y = rand() % screenHeight;
		starCoor[i].z = rand() % 500;
		starCoor[i].starSize = rand() % 5;
	}
	if (!HAPI.Initialise(screenWidth, screenHeight, "Games Engine Construction ICA - V8008106"))
		return;

	BYTE* screen = HAPI.GetScreenPointer();
	const HAPI_TKeyboardData& keyboardData = HAPI.GetKeyboardData();
	HAPI.SetShowFPS(true);

	while (HAPI.Update())
	{
		ClearToColour(screen, screenWidth, screenHeight, HAPI_TColour::BLACK);
		for (int i = 0; i < kNumStars; i++)
		{
			//Project the stars from 3D space into 2D space
			float Sx = ((eyeDistance * (starCoor[i].x - (CentreX))) / (starCoor[i].z + eyeDistance)) + (CentreX);
			float Sy = ((eyeDistance * (starCoor[i].y - (CentreY))) / (starCoor[i].z + eyeDistance)) + (CentreY);

			//Render the stars
			if ((Sx < screenWidth && Sx > 0) && (Sy < screenHeight && Sy > 0)) 
			{ 
				//Change the colour and the size depending on the z position
				if (starCoor[i].z < 500.0f)
				{
					starColour = HAPI_TColour::WHITE;
					starCoor[i].starSize = 1;
				}
				if (starCoor[i].z < 400.0f)
				{
					starColour = HAPI_TColour(255, 245, 235, 255);
					starCoor[i].starSize = 2;
				}
				if (starCoor[i].z < 300.0f)
				{
					starColour = HAPI_TColour(255, 235, 215, 255);
					starCoor[i].starSize = 3;
				}
				if (starCoor[i].z < 200.0f)
				{
					starColour = HAPI_TColour(255, 225, 195, 255);
					starCoor[i].starSize = 4;
				}
				if (starCoor[i].z < 100.0f)
				{
					starColour = HAPI_TColour(255, 215, 175, 255);
					starCoor[i].starSize = 5;
				}
				if (starCoor[i].starSize > 0)
				{
					//Increase the size of the star 
					for (int starWidth = 0; starWidth < starCoor[i].starSize; starWidth++)
					{
						for (int starHeight = 0; starHeight < starCoor[i].starSize; starHeight++)
						{
							int offset = ((Sy + starHeight) * screenWidth + (Sx + starWidth)) * 4;
							BYTE* pnter = screen + offset;
							if ((Sx + starWidth < screenWidth && Sx > 0) && (Sy + starHeight < screenHeight && Sy > 0))
							{
								//Render the star
								memcpy(pnter, &starColour, 4);
							}
						}
					}
				}
				else			
				{
					//Render the star
					int offset = (Sy * screenWidth + Sx) * 4;
					BYTE* pnter = screen + offset;
					memcpy(pnter, &starColour, 4);
				}
			}

			//Move the stars
			starCoor[i].z -= 0.1f;
			if (starCoor[i].z <= 0)
			{
				starCoor[i].x = rand() % screenWidth;
				starCoor[i].y = rand() % screenHeight;
				starCoor[i].z = 500;
			}				
		}
		//Display controls
		HAPI.RenderText(10, 20, HAPI_TColour::YELLOW, "Change the eye distance - ARROWS (UP, DOWN)", 14, HAPI_TextStyle::eRegular);
		HAPI.RenderText(10, 40, HAPI_TColour::YELLOW, "Move the point where stars spawn - WASD", 14, HAPI_TextStyle::eRegular);

		//Control the stars
		if (keyboardData.scanCode[HK_UP]) { eyeDistance += 1; }
		if (eyeDistance > 10)
		{
			if (keyboardData.scanCode[HK_DOWN]) { eyeDistance -= 1; }
		}
		if (keyboardData.scanCode['W']) { CentreY -= 1; }
		if (keyboardData.scanCode['A']) { CentreX -= 1; }
		if (keyboardData.scanCode['S']) { CentreY += 1; }
		if (keyboardData.scanCode['D']) { CentreX += 1; }
	}
}

void ClearToColour(BYTE* screen, const int& screenWidth, const int& screenHeight, const HAPI_TColour& argColour)
{
	BYTE* temp = screen;
	for (int i = 0; i < screenWidth * screenHeight; i++)
	{
		memcpy(temp, &argColour, 4);
		temp += 4;
	}
}

