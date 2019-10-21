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
	vector2<int> spriteSize{ 0 , 0 };
	BYTE* texture{ nullptr };

public:
	Sprite();
	~Sprite();
	bool Initialisation(const std::string& filename);
	void Render(BYTE* screen, const int& screenWidth, int posX, int posY);

	int GetSpriteX() const { return spriteSize.widthX; }
	int GetSpriteY() const { return spriteSize.heightY; }
};