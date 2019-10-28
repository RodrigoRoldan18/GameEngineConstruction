#include "Sprite.h"
#include <algorithm>

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
	rect.left = 0;
	rect.top = 0;
	rect.right = spriteSize.widthX;
	rect.bottom = spriteSize.heightY;
	return true;
}

void Sprite::ClipBlit(BYTE* dest, const Rectangle& destRect, int& posX, int& posY)
{
	//Create a new source rectangle without position
	Rectangle tempClippedRect(rect);
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
		posX = std::max(0, posX);
		posY = std::max(0, posY);
	}	

	//get the top left position of the screen
	BYTE* screenPnter = dest + (size_t)(posX + posY * destRect.Width()) * 4;
	//Temporary pointer for the texture data
	BYTE* texturePnter = texture + (tempClippedRect.left + tempClippedRect.top * destRect.Width()) * 4;

	for (int y = 0; y < tempClippedRect.Height(); y++)
	{
		for (int x = 0; x < tempClippedRect.Width(); x++)
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
		screenPnter += ((size_t)destRect.Width() - tempClippedRect.Width()) * 4;
		texturePnter += spriteSize.widthX - tempClippedRect.Width() * 4;
	}
}