#include "Player.h"
#include "Visualisation.h"

void Player::Update(const Visualisation& viz)
{
	InputHandling();
	Movement();
	viz.DrawSprite(gfxName, position, currentAnimFrame, frame);
	currentAnimFrame++;
	if (currentAnimFrame == animationFrames) { currentAnimFrame = 0; }
}

void Player::InputHandling()
{
	const HAPI_TKeyboardData& keyboardData = HAPI.GetKeyboardData();
	const HAPI_TControllerData& controllerData = HAPI.GetControllerData(0);
	if (keyboardData.scanCode['W'])
	{
		direction = EDirection::EUp;
	}
	else if (keyboardData.scanCode['A'])
	{
		direction = EDirection::ELeft;
	}
	else if (keyboardData.scanCode['S'])
	{
		direction = EDirection::EDown;
	}
	else if (keyboardData.scanCode['D'])
	{
		direction = EDirection::ERight;
	}
	else
	{
		direction = EDirection::EStill;
	}
	if (controllerData.isAttached)
	{
		if (controllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y] > 15000)
		{
			direction = EDirection::EUp;
		}
		else if (controllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X] < -15000)
		{
			direction = EDirection::ELeft;
		}
		else if (controllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y] < -15000)
		{
			direction = EDirection::EDown;
		}
		else if (controllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X] > 15000)
		{
			direction = EDirection::ERight;
		}
	}
}
