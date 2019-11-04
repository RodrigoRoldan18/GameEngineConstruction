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
#include "Vector2.h"

// HAPI itself is wrapped in the HAPISPACE namespace
using namespace HAPISPACE;

// Every HAPI program has a HAPI_Main as an entry point
// When this function exits the program will close down

void HAPI_Main()
{
	//-------------------------------
	const HAPI_TKeyboardData& keyboardData = HAPI.GetKeyboardData();
	HAPI.SetShowFPS(true);
	vector2<int> playerPos{ 0 , 100 };
	bool doRumble{ false };

	Visualisation* m_visualisation{ new Visualisation };

	//-------------------------------	
	if (!m_visualisation->CreateSprite("Data\\alphaThing.tga", "Player"))
	{
		HAPI.UserMessage("Couldn't load the texture for the Player", "Warning");
		return;
	}

	while (HAPI.Update())
	{
		const HAPI_TControllerData& controllerData = HAPI.GetControllerData(0);
		m_visualisation->ClearToColour(HAPI_TColour::BLACK);
		m_visualisation->DrawSprite("Player", playerPos.widthX, playerPos.heightY);

		if (controllerData.isAttached)
		{
			if (keyboardData.scanCode['W'] || controllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y] > 15000)
			{
				playerPos.heightY--;
			}
			if (keyboardData.scanCode['A'] || controllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X] < -15000)
			{
				playerPos.widthX--;
			}
			if (keyboardData.scanCode['S'] || controllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y] < -15000)
			{
				playerPos.heightY++;
			}
			if (keyboardData.scanCode['D'] || controllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X] > 15000)
			{
				playerPos.widthX++;
			}
		}

		if (playerPos.widthX < 600 && playerPos.widthX > 500)
		{
			if (playerPos.heightY < 400 && playerPos.heightY > 300)

			{
				HAPI.SetControllerRumble(0, 20000, 20000);
			}
		}
		else
		{
			HAPI.SetControllerRumble(0, 0, 0);
		}
	}
	delete m_visualisation;
	HAPI.SetControllerRumble(0, 0, 0);
}
