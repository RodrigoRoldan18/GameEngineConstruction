#pragma once

// Include the HAPI header to get access to all of HAPIs interfaces
#include <HAPI_lib.h>
#include "Rectangle.h"
#include "Vector2.h"
// HAPI itself is wrapped in the HAPISPACE namespace
using namespace HAPISPACE;

class Sprite
{
	vector2<int> spriteSize{ 0 , 0 };
	BYTE* texture{ nullptr };
	Rectangle sourceRect;

public:
	Sprite();
	~Sprite();
	bool Initialisation(const std::string& filename);
	void ClipBlit(BYTE* dest, const Rectangle& destRect, const vector2<int>& position, int animationFrame, const Rectangle& argFrame);
	void Render(BYTE* dest, const int& screenWidth, const vector2<int>& position, int animationFrame, const Rectangle& argFrame);

	int GetSpriteX() const { return spriteSize.widthX; }
	int GetSpriteY() const { return spriteSize.heightY; }
};