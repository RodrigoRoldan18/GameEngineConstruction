#include "Visualisation.h"

Visualisation* Visualisation::instance{ nullptr };

Visualisation& Visualisation::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new Visualisation();
	}
	return *instance;
}

Visualisation::Visualisation()
{
	screenSize.widthX = 950;//1240
	screenSize.heightY = 768;//768
	if (!HAPI.Initialise(screenSize.widthX, screenSize.heightY, "Games Engine Construction ICA - V8008106"))
		return;	
	screenPnter = HAPI.GetScreenPointer();

	bgRect.left = 0;
	bgRect.top = 0;
	bgRect.right = screenSize.widthX;
	bgRect.bottom = screenSize.heightY;
}

Visualisation::~Visualisation()
{
	for (auto& sprite : mapSprite)
	{
		delete sprite.second;
	}
	delete instance;
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

bool Visualisation::CreateSprite(const std::string& filename, const std::string& name)
{
	Sprite* newSprite = new Sprite();
	if (!newSprite->Initialisation(filename))
	{
		delete newSprite;
		return false;
	}
		
	mapSprite[name] = newSprite;
	return true;
}

void Visualisation::DrawSprite(const std::string& name, const vector2<int>& position, int animationFrame, const Rectangle& argFrame) const
{
	if (!mapSprite.at(name))
	{
		HAPI.UserMessage("Can't draw the " + name, "Warning");
		return;
	}
	mapSprite.at(name)->ClipBlit(screenPnter, bgRect, position, animationFrame, argFrame);
}
