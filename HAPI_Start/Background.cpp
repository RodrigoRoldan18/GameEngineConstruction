#include "Background.h"
#include "Visualisation.h"

void Background::Update(const Visualisation& viz)
{
	InputHandling(viz);
	viz.DrawSprite(gfxName, position);
	viz.DrawSprite(gfxName, extraBgPos);//extra
}

void Background::InputHandling(const Visualisation& viz)
{
	const HAPI_TKeyboardData& keyboardData = HAPI.GetKeyboardData();
	const HAPI_TControllerData& controllerData = HAPI.GetControllerData(0);
	if (controllerData.isAttached)
	{
		if (keyboardData.scanCode['A'] || controllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X] < -15000)
		{
			position.widthX++;
			extraBgPos.widthX++;
			if (position.widthX == viz.GetScreenWidth()) { position.widthX = 0; }
			if (position.widthX > 0)
				extraBgPos = { position.widthX - viz.GetScreenWidth(), position.heightY }; //left
		}
		if (keyboardData.scanCode['D'] || controllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X] > 15000)
		{
			position.widthX--;
			extraBgPos.widthX--;
			if (position.widthX == -viz.GetScreenWidth()) { position.widthX = 0; }
			if(position.widthX < 0)
				extraBgPos = { position.widthX + viz.GetScreenWidth(), position.heightY }; //right
		}
	}
}
