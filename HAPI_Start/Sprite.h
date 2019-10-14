#pragma once

// Include the HAPI header to get access to all of HAPIs interfaces
#include <HAPI_lib.h>

// HAPI itself is wrapped in the HAPISPACE namespace
using namespace HAPISPACE;

class Sprite
{
	//Move texture to here

public:
	void Blit(BYTE* screen, const int& screenWidth, BYTE* texture, int textureWidth, int textureHeight, int posX, int posY);
};

