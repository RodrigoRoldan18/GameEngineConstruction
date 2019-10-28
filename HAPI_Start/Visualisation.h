#pragma once

#include <unordered_map>
#include <string>
// Include the HAPI header to get access to all of HAPIs interfaces
#include <HAPI_lib.h>
#include "Rectangle.h"
// HAPI itself is wrapped in the HAPISPACE namespace
using namespace HAPISPACE;

class Sprite;

class Visualisation
{
	template<class T>
	struct vector2
	{
		T widthX;
		T heightY;
	};
	vector2<int> screenSize{ 0 , 0 };
	BYTE* screenPnter{ nullptr };
	std::unordered_map<std::string, Sprite*> mapSprite;

	Rectangle rect;

	vector2<int> playerPos{ 0 , 0 };//find another way to store the sprite position on the screen

public:
	Visualisation();
	void ClearToColour(const HAPI_TColour& argColour);
	void Update();
	bool CreateSprite(const std::string& filename, const std::string& name);
	void DrawSprite(const std::string& name, int spriteX, int spriteY) const;

};
