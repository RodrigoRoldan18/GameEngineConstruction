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

void HAPI_Main()
{
	//-------------------------------
	const HAPI_TKeyboardData& keyboardData = HAPI.GetKeyboardData();
	const HAPI_TControllerData& controllerData = HAPI.GetControllerData(0);
	HAPI.SetShowFPS(true);

	Visualisation* m_visualisation{ new Visualisation };	
	//-------------------------------	
	if(!m_visualisation->CreateSprite("Data\\background.tga", "Background"))
		HAPI.UserMessage("Couldn't load the texture", "Warning");
	if (!m_visualisation->CreateSprite("Data\\playerSprite.tga", "Player"))
		HAPI.UserMessage("Couldn't load the texture", "Warning");
	if(!m_visualisation->CreateSprite("Data\\alphaThing.tga", "WeirdThing"))
		HAPI.UserMessage("Couldn't load the texture", "Warning");

	while (HAPI.Update())
	{
		m_visualisation->ClearToColour(HAPI_TColour::BLACK);
		m_visualisation->DrawSprite("Background", 0, 0);
		m_visualisation->DrawSprite("WeirdThing", 0, 0);
		m_visualisation->DrawSprite("Player", 100, 100);
	}
	//CONTROL THE PLAYER THING
}
