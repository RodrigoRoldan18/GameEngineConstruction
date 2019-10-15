#include "Visualisation.h"
#include "Sprite.h"

Visualisation::Visualisation()
{
	screenSize.widthX = 1024;
	screenSize.heightY = 768;
	if (!HAPI.Initialise(screenSize.widthX, screenSize.heightY, "Games Engine Construction ICA - V8008106"))
		return;	
	screenPnter = HAPI.GetScreenPointer();
}

void Visualisation::ClearToColour(const HAPI_TColour& argColour)
{
	BYTE* temp = screenPnter;
	for (int i = 0; i < screenSize.widthX * screenSize.heightY; i++)
	{
		memcpy(temp, &argColour, 4);
		temp += 4;
	}
}

int Visualisation::GetWidth()
{
	return screenSize.widthX;
	//return screenWidth;
}

int Visualisation::GetHeight()
{
	return screenSize.heightY;
	//return screenHeight; 
}

BYTE* Visualisation::GetScreenPnter()
{
	return screenPnter;
}


bool Visualisation::CreateSprite(const std::string& filename, const std::string& name)
{
	Sprite* newSprite = new Sprite();
	if (!newSprite->Initialisation(filename))
		return false;
	mapSprite[name] = newSprite;
	return true;
}

void Visualisation::DrawSprite(const std::string& name, const int& sX, const int& sY) const
{
	/*if (!mapSprite.find(name))
		HAPI.UserMessage("Sprite not found in the map", "Warning");*/
	mapSprite.at(name)->Render(screenPnter, screenSize.widthX, sX, sY);
	
}
