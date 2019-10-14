#if defined(DEBUG) | defined(_DEBUG)
	#include <crtdbg.h>
	#define new new(_NORMAL_BLOCK,__FILE__,__LINE__)
#endif

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
#include "Visualisation.h"

// HAPI itself is wrapped in the HAPISPACE namespace
using namespace HAPISPACE;

// Every HAPI program has a HAPI_Main as an entry point
// When this function exits the program will close down
//-----------------------------------------------------
//void ClearToColour(BYTE* screen, const int& screenWidth, const int& screenHeight, const HAPI_TColour& argColour);
void Blit(BYTE* screen, const int& screenWidth, BYTE* texture, int textureWidth, int textureHeight, int posX, int posY);
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
	int eyeDistance(100);
	int CentreX(1024 / 2);
	int CentreY(768 / 2);
	HAPI_TColour starColour;

	int textureWidth, textureHeight;
	BYTE* texture{ nullptr };
	int texPosX{ 100 }, texPosY{ 100 };

	Visualisation* m_visualisation{ new Visualisation };

	const HAPI_TKeyboardData& keyboardData = HAPI.GetKeyboardData();
	const HAPI_TControllerData& controllerData = HAPI.GetControllerData(0);
	HAPI.SetShowFPS(true);
	//-------------------------------

	//Initialise the stars
	Scoordinates3D starCoor[kNumStars];
	for (int i = 0; i < kNumStars; i++)
	{
		starCoor[i].x = rand() % m_visualisation->GetWidth();
		starCoor[i].y = rand() % m_visualisation->GetHeight();
		starCoor[i].z = rand() % 500;
		starCoor[i].starSize = rand() % 5;
	}
	
	//Load the textures(sprites)
	if (!HAPI.LoadTexture("Data\\playerSprite.tga", &texture, textureWidth, textureHeight))
		HAPI.UserMessage("Texture didn't load correctly", "Warning");

	while (HAPI.Update())
	{
		m_visualisation->ClearToColour(HAPI_TColour::BLACK);
		for (int i = 0; i < kNumStars; i++)
		{
			//Project the stars from 3D space into 2D space
			float Sx = ((eyeDistance * (starCoor[i].x - (CentreX))) / (starCoor[i].z + eyeDistance)) + (CentreX);
			float Sy = ((eyeDistance * (starCoor[i].y - (CentreY))) / (starCoor[i].z + eyeDistance)) + (CentreY);

			//Render the stars
			if ((Sx < m_visualisation->GetWidth() && Sx > 0) && (Sy < m_visualisation->GetHeight() && Sy > 0)) 
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
							int offset = ((Sy + starHeight) * m_visualisation->GetWidth() + (Sx + starWidth)) * 4;
							BYTE* pnter = m_visualisation->GetScreenPnter() + offset;
							if ((Sx + starWidth < m_visualisation->GetWidth() && Sx > 0) && (Sy + starHeight < m_visualisation->GetHeight() && Sy > 0))
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
					int offset = (Sy * m_visualisation->GetWidth() + Sx) * 4;
					BYTE* pnter = m_visualisation->GetScreenPnter() + offset;
					memcpy(pnter, &starColour, 4);
				}
			}

			//Move the stars
			starCoor[i].z -= 0.1f;
			if (starCoor[i].z <= 0)
			{
				starCoor[i].x = rand() % m_visualisation->GetWidth();
				starCoor[i].y = rand() % m_visualisation->GetHeight();
				starCoor[i].z = 500;
			}				
		}
		//Control the spaceship
		if (controllerData.isAttached)
		{
			if (controllerData.digitalButtons[HK_DIGITAL_DPAD_RIGHT]) { texPosX++; }
			if (controllerData.digitalButtons[HK_DIGITAL_DPAD_LEFT]) { texPosX--; }
		}
		if (keyboardData.scanCode['L']) { texPosX++; } //add the area of the texture
		if (keyboardData.scanCode['J']) { texPosX--; }
		if (keyboardData.scanCode['I']) { texPosY--; }
		if (keyboardData.scanCode['K']) { texPosY++; }
		//Render the spaceship
		Blit(m_visualisation->GetScreenPnter(), m_visualisation->GetWidth(), texture, textureWidth, textureHeight, texPosX, texPosY);
		//Display controls
		HAPI.RenderText(10, 20, HAPI_TColour::YELLOW, "Change the eye distance - ARROWS (UP, DOWN)", 14, HAPI_TextStyle::eRegular);
		HAPI.RenderText(10, 40, HAPI_TColour::YELLOW, "Move the point where stars spawn - WASD", 14, HAPI_TextStyle::eRegular);
		HAPI.RenderText(10, 60, HAPI_TColour::YELLOW, "Control the spaceship - IJKL", 14, HAPI_TextStyle::eRegular);

		//Control the stars
		if (keyboardData.scanCode[HK_UP]) { eyeDistance++; }
		if (eyeDistance > 10)
		{
			if (keyboardData.scanCode[HK_DOWN]) { eyeDistance--; }
		}
		if (keyboardData.scanCode['W']) { CentreY--; }
		if (keyboardData.scanCode['A']) { CentreX--; }
		if (keyboardData.scanCode['S']) { CentreY++; }
		if (keyboardData.scanCode['D']) { CentreX++; }
	}
	delete[] texture;
}

void Blit(BYTE* screen, const int& screenWidth, BYTE* texture, int textureWidth, int textureHeight, int posX, int posY)
{
	//get the top left position of the screen
	BYTE* screenPnter = screen + (posX + posY * screenWidth) * 4;
	//Temporary pointer for the texture data
	BYTE* texturePnter = texture;

	//HANDLE SPECIAL CASES. ALPHA = 0 & 255
	for (int y = 0; y < textureHeight; y++)
	{
		for (int x = 0; x < textureWidth; x++)
		{
			BYTE blue = texturePnter[0];
			BYTE green = texturePnter[1];
			BYTE red = texturePnter[2];
			BYTE alpha = texturePnter[3];			

			screenPnter[0] = screenPnter[0] + ((alpha * (blue - screenPnter[0])) >> 8);
			screenPnter[1] = screenPnter[1] + ((alpha * (green - screenPnter[1])) >> 8);
			screenPnter[2] = screenPnter[2] + ((alpha * (red - screenPnter[2])) >> 8);

			//Move texture pointer to next line
			texturePnter += 4;
			//Move screen pointer to the next line
			screenPnter += 4;
		}
		screenPnter += (screenWidth - textureWidth) * 4;
	}
}

