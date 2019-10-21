#include "Sprite.h"

Sprite::Sprite()
{
}

Sprite::~Sprite()
{
	//delete[] this;
}

bool Sprite::Initialisation(const std::string& filename)
{
	if (!HAPI.LoadTexture(filename, &texture, spriteSize.widthX, spriteSize.heightY))
	{
		HAPI.UserMessage("Texture " + filename +" didn't load correctly", "Warning");
		return false;
	}
	return true;
}

void Sprite::Render(BYTE* screen, const int& screenWidth, int posX, int posY)
{
	//get the top left position of the screen
	BYTE* screenPnter = screen + (size_t)(posX + posY * screenWidth) * 4;
	//Temporary pointer for the texture data
	BYTE* texturePnter = texture;

	for (int y = 0; y < spriteSize.heightY; y++)
	{
		for (int x = 0; x < spriteSize.widthX; x++)
		{
			BYTE red = texturePnter[0];
			BYTE green = texturePnter[1];
			BYTE blue = texturePnter[2];
			BYTE alpha = texturePnter[3];
			
			if (alpha == 255)
			{
				//screen = texture
				screenPnter[0] = red;
				screenPnter[1] = green;
				screenPnter[2] = blue;
			}
			else if(alpha > 0)
			{
				screenPnter[0] = screenPnter[0] + ((alpha * (red - screenPnter[0])) >> 8);
				screenPnter[1] = screenPnter[1] + ((alpha * (green - screenPnter[1])) >> 8);
				screenPnter[2] = screenPnter[2] + ((alpha * (blue - screenPnter[2])) >> 8);
			}			
			
			//Move texture pointer to next line
			texturePnter += 4;
			//Move screen pointer to the next line
			screenPnter += 4;
		}
		screenPnter += ((size_t)screenWidth - spriteSize.widthX) * 4;
	}
}