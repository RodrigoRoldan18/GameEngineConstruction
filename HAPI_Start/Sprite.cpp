#include "Sprite.h"
#include <algorithm>

Sprite::Sprite()
{
}

Sprite::~Sprite()
{
}

bool Sprite::Initialisation(const std::string& filename)
{
	if (!HAPI.LoadTexture(filename, &texture, spriteSize.widthX, spriteSize.heightY))
	{
		HAPI.UserMessage("Texture " + filename +" didn't load correctly", "Warning");
		return false;
	}
	sourceRect.left = 0;
	sourceRect.top = 0;
	sourceRect.right = spriteSize.widthX;
	sourceRect.bottom = spriteSize.heightY;
	return true;
}

void Sprite::ClipBlit(BYTE* dest, const Rectangle& destRect, int& posX, int& posY)
{

	//Create a new source rectangle without 
	Rectangle tempClippedRect(sourceRect);
	//Check for completely outside or inside
	if (tempClippedRect.CompletelyOutside(destRect))
	{
		return;
	}
	if (!tempClippedRect.CompletelyInside(destRect))
	{
		//Translato to screen space
		tempClippedRect.Translate(posX, posY);
		//Clip against destination rectangle
		tempClippedRect.ClippingTo(destRect);
		//Translate back into source space
		tempClippedRect.Translate(-posX, -posY);

		//Clamping to negative
		posX = std::max(posX, 0);
		posY = std::max(posY, 0);
	}		

	//get the top left position of the screen
	BYTE* destPnter = dest + (size_t)(posX + posY * destRect.Width()) * 4;
	//Temporary pointer for the texture data
	BYTE* sourcePnter = texture + (tempClippedRect.left + tempClippedRect.top * tempClippedRect.Width()) * 4;

	for (int y = 0; y < tempClippedRect.Height(); y++)
	{
		for (int x = 0; x < tempClippedRect.Width(); x++)
		{
			BYTE red = sourcePnter[0];
			BYTE green = sourcePnter[1];
			BYTE blue = sourcePnter[2];
			BYTE alpha = sourcePnter[3];
			
			if (alpha == 255)
			{
				//screen = texture
				destPnter[0] = red;
				destPnter[1] = green;
				destPnter[2] = blue;
			}
			else if(alpha > 0)
			{
				destPnter[0] = destPnter[0] + ((alpha * (red - destPnter[0])) >> 8);
				destPnter[1] = destPnter[1] + ((alpha * (green - destPnter[1])) >> 8);
				destPnter[2] = destPnter[2] + ((alpha * (blue - destPnter[2])) >> 8);
			}			
			
			//Move texture pointer to next line
			sourcePnter += 4;
			//Move screen pointer to the next line
			destPnter += 4;
		}
		destPnter += ((size_t)destRect.Width() - sourceRect.Width()) * 4;
	}
}