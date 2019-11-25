#include "Sprite.h"
#include <algorithm>

Sprite::Sprite()
{
}

Sprite::~Sprite()
{
	delete[] texture;
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

void Sprite::ClipBlit(BYTE* dest, const Rectangle& destRect, const vector2<int>& position)
{
	vector2<int> tempPos = position;
	//Create a new source rectangle without 
	Rectangle tempClippedRect(sourceRect);
	//Translato to screen space
	tempClippedRect.Translate(tempPos.widthX, tempPos.heightY);

	if (tempClippedRect.CompletelyOutside(destRect))
	{
		return;
	}
	if (tempClippedRect.CompletelyInside(destRect))
	{		
		//Go to the other function for optimisation
		Render(dest, destRect.Width(), position);
		return;		
	}
	if(!tempClippedRect.CompletelyOutside(destRect) && !tempClippedRect.CompletelyInside(destRect))
	{
		//Clip against destination rectangle
		tempClippedRect.ClippingTo(destRect);
	}
	//Translate back into source space
	tempClippedRect.Translate(-tempPos.widthX, -tempPos.heightY);

	//Clamping to negative
	tempPos.widthX = std::max(tempPos.widthX, 0);
	tempPos.heightY = std::max(tempPos.heightY, 0);

	//get the top left position of the screen
	BYTE* destPnter = dest + (tempPos.widthX + tempPos.heightY * (size_t)destRect.Width()) * 4;	//gets the point in the destination where to start drawing
	//Temporary pointer for the texture data
	BYTE* sourcePnter = texture + (tempClippedRect.left + tempClippedRect.top * (size_t)sourceRect.Width()) * 4;	//gets the point where to start drawing the texture

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
		destPnter += ((size_t)destRect.Width() - tempClippedRect.Width()) * 4;	
		sourcePnter += (sourceRect.Width() - (size_t)tempClippedRect.Width()) * 4;
	}
}

void Sprite::Render(BYTE* dest, const int& screenWidth, const vector2<int>& position)
{
	//get the top left position of the screen
	BYTE* screenPnter = dest + (position.widthX + position.heightY * (size_t)screenWidth) * 4;
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
			else if (alpha > 0)
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