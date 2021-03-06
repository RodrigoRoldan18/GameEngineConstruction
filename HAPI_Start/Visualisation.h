#pragma once

#include <unordered_map>
#include <string>
// Include the HAPI header to get access to all of HAPIs interfaces
#include <HAPI_lib.h>
#include "Rectangle.h"
#include "Vector2.h"
#include "Sprite.h"

// HAPI itself is wrapped in the HAPISPACE namespace
using namespace HAPISPACE;

class Visualisation
{
private:
	vector2<int> screenSize{ 0 , 0 };
	BYTE* screenPnter{ nullptr };
	Rectangle bgRect;

	std::unordered_map<std::string, Sprite*> mapSprite;
	static Visualisation* instance;

	Visualisation();

public:
	static Visualisation& GetInstance();
	~Visualisation();
	void ClearToColour(const HAPI_TColour& argColour);
	bool CreateSprite(const std::string& filename, const std::string& name);
	void DrawSprite(const std::string& name, const vector2<int>& position, int animationFrame, const Rectangle& argFrame) const;

	int GetScreenWidth() const { return screenSize.widthX; }
	int GetScreenHeight() const { return screenSize.heightY; }
	Rectangle GetRect(const std::string& spriteName) const { return mapSprite.at(spriteName)->GetRect(); }
};

#define VIZ Visualisation::GetInstance()
