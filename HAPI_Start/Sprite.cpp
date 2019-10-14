#include "Sprite.h"

void Sprite::Blit(BYTE* screen, const int& screenWidth, BYTE* texture, int textureWidth, int textureHeight, int posX, int posY)
{
	//get the top left position of the screen
	BYTE* screenPnter = screen + (posX + posY * screenWidth) * 4;
	//Temporary pointer for the texture data
	BYTE* texturePnter = texture;

	//HANDLE SPECIAL CASES. ALPHA = 0 & 255
	for (int y = 0; y < textureHeight; y++)
	{
		for (int x = 0; x < textureWidth; x++)
		{
			BYTE blue = texturePnter[0];
			BYTE green = texturePnter[1];
			BYTE red = texturePnter[2];
			BYTE alpha = texturePnter[3];

			screenPnter[0] = screenPnter[0] + ((alpha * (blue - screenPnter[0])) >> 8);
			screenPnter[1] = screenPnter[1] + ((alpha * (green - screenPnter[1])) >> 8);
			screenPnter[2] = screenPnter[2] + ((alpha * (red - screenPnter[2])) >> 8);

			//Move texture pointer to next line
			texturePnter += 4;
			//Move screen pointer to the next line
			screenPnter += 4;
		}
		screenPnter += (screenWidth - textureWidth) * 4;
	}
}
