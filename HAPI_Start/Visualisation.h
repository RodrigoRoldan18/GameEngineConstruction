#pragma once

#include "Sprite.h"
#include <map>
// Include the HAPI header to get access to all of HAPIs interfaces
#include <HAPI_lib.h>
// HAPI itself is wrapped in the HAPISPACE namespace
using namespace HAPISPACE;

class Visualisation
{
	template<class T>
	struct vector2
	{
		T widthX;
		T heightY;
	};
	vector2<int> screenSize;
	BYTE* screenPnter;
	std::map<std::string, Sprite*> Sprites;

public:
	Visualisation();
	void ClearToColour(const HAPI_TColour& argColour);
	int GetWidth();
	int GetHeight();
	BYTE* GetScreenPnter();
};
