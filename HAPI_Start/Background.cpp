#include "Background.h"
#include "Visualisation.h"


void Background::Update(const Visualisation& viz)
{
	vector2<int> tempBgPos;
	InputHandling(viz);
	viz.DrawSprite(gfxName, position);
	tempBgPos = { position.widthX - viz.GetScreenWidth(), position.heightY };
	viz.DrawSprite(gfxName, tempBgPos);//extra
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
			if (position.widthX == viz.GetScreenWidth()) { position.widthX = 0; }
		}
		if (keyboardData.scanCode['D'] || controllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X] > 15000)
		{
			position.widthX--;
			if (position.widthX == -viz.GetScreenWidth()) { position.widthX = 0; }
		}
	}
}
