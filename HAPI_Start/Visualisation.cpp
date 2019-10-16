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

void Visualisation::Update()
{
	const HAPI_TKeyboardData& keyboardData = HAPI.GetKeyboardData();
	while (HAPI.Update())
	{
		ClearToColour(HAPI_TColour::BLACK);
		DrawSprite("Background", 0, 0);
		DrawSprite("WeirdThing", 0, 0);
		DrawSprite("Player", playerPos.widthX, playerPos.heightY);

		if (keyboardData.scanCode['W'] && playerPos.heightY > 0) { playerPos.heightY--; }
		if (keyboardData.scanCode['A'] && playerPos.widthX > 0) { playerPos.widthX--; }
		if (keyboardData.scanCode['S'] && playerPos.heightY < screenSize.heightY - mapSprite.at("Player")->GetSpriteY()) { playerPos.heightY++; } //am I allowed to use GetFunctions?
		if (keyboardData.scanCode['D'] && playerPos.widthX < screenSize.widthX - mapSprite.at("Player")->GetSpriteX()) { playerPos.widthX++; } 
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

void Visualisation::DrawSprite(const std::string& name, const int& spriteX, const int& spriteY) const
{
	/*if (!mapSprite.find(name))
		HAPI.UserMessage("Sprite not found in the map", "Warning");*/
	mapSprite.at(name)->Render(screenPnter, screenSize.widthX, spriteX, spriteY);
	
}
