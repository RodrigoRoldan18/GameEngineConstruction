#include "Visualisation.h"
#include "Sprite.h"

Visualisation::Visualisation()
{
	screenSize.widthX = 1024;
	screenSize.heightY = 768;
	if (!HAPI.Initialise(screenSize.widthX, screenSize.heightY, "Games Engine Construction ICA - V8008106"))
		return;	
	screenPnter = HAPI.GetScreenPointer();

	rect.left = 0;
	rect.top = 0;
	rect.right = screenSize.widthX;
	rect.bottom = screenSize.heightY;
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

void Visualisation::Update()
{
	const HAPI_TKeyboardData& keyboardData = HAPI.GetKeyboardData();
	while (HAPI.Update())
	{
		ClearToColour(HAPI_TColour::BLACK);
		DrawSprite("Background", 0, 0);
		DrawSprite("Player", playerPos.widthX, playerPos.heightY);

		if (mapSprite.at("Player"))
		{
			if (keyboardData.scanCode['W'])
			{
				playerPos.heightY--;
			}
			if (keyboardData.scanCode['A'])
			{
				playerPos.widthX--;
			}
			if (keyboardData.scanCode['S'])
			{
				playerPos.heightY++;
			}
			if (keyboardData.scanCode['D'])
			{
				playerPos.widthX++;
			}
		}		
	}
}

bool Visualisation::CreateSprite(const std::string& filename, const std::string& name)
{
	Sprite* newSprite = new Sprite();
	if (!newSprite->Initialisation(filename))
		return false;
	mapSprite[name] = newSprite;
	return true;
}

void Visualisation::DrawSprite(const std::string& name, int spriteX, int spriteY) const
{
	if (!mapSprite.at(name))
	{
		HAPI.UserMessage("Can't draw the " + name, "Warning");
		return;
	}
	mapSprite.at(name)->ClipBlit(screenPnter, rect, spriteX, spriteY);
}
