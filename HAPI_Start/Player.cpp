#include "Player.h"
#include "Visualisation.h"

void Player::Update(const Visualisation& viz)
{
	InputHandling();
	viz.DrawSprite(gfxName, position);	
}

void Player::InputHandling()
{
	const HAPI_TKeyboardData& keyboardData = HAPI.GetKeyboardData();
	const HAPI_TControllerData& controllerData = HAPI.GetControllerData(0);
	if (controllerData.isAttached)
	{
		if (keyboardData.scanCode['W'] || controllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y] > 15000)
		{
			position.heightY--;
		}
		if (keyboardData.scanCode['A'] || controllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X] < -15000)
		{
			position.widthX--;
			//backgroundPos.widthX++;
			//if (backgroundPos.widthX == m_viz->GetScreenWidth()) { backgroundPos.widthX = 0; }
		}
		if (keyboardData.scanCode['S'] || controllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y] < -15000)
		{
			position.heightY++;
		}
		if (keyboardData.scanCode['D'] || controllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X] > 15000)
		{
			position.widthX++;
			//backgroundPos.widthX--;
			//if (backgroundPos.widthX == -m_viz->GetScreenWidth()) { backgroundPos.widthX = 0; }
		}
	}	
}
