#pragma once

// Include the HAPI header to get access to all of HAPIs interfaces
#include <HAPI_lib.h>
// HAPI itself is wrapped in the HAPISPACE namespace
using namespace HAPISPACE;

class Sprite
{
	template<class T>
	struct vector2
	{
		T widthX;
		T heightY;
	};
	vector2<int> spriteSize;
	BYTE* texture;
	vector2<int> texturePos;

public:
	Sprite(const std::string& filename);
	~Sprite();
	void Blit(BYTE* screen, const int& screenWidth, BYTE* texture, int textureWidth, int textureHeight, int posX, int posY);
};

