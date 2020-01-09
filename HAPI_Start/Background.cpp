#include "Background.h"
#include "Visualisation.h"
#include "World.h"

Background::Background(const std::string& name) : Entity(name) 
{
	frame = Rectangle(0, 960, 0, 960);
	speed = 4;
}

void Background::Update(const float s)
{
	Render(s);
	vector2<int> interExtraPos{ extraBgOldPos + (extraBgPos - extraBgOldPos) * s };
	VIZ.DrawSprite(gfxName, interExtraPos, 0, frame);//extra
}

void Background::InputHandling()
{
	const HAPI_TKeyboardData& keyboardData = HAPI.GetKeyboardData();
	const HAPI_TControllerData& controllerData = HAPI.GetControllerData(0);

	vector2<int> tempPos{ GetPosition() };
	vector2<int> tempExtraPos{ extraBgPos };

	if (WORLD.isBgMoving())
	{
		if (keyboardData.scanCode['A'])
		{
			direction = EDirection::ERight;
			tempExtraPos.widthX += speed;
			if (tempPos.widthX == frame.Width()) { tempPos.widthX = 0; }
			if (tempPos.widthX > 0)
				tempExtraPos = { tempPos.widthX - VIZ.GetScreenWidth() , tempPos.heightY };
		}
		if (keyboardData.scanCode['D'])
		{
			direction = EDirection::ELeft;
			tempExtraPos.widthX -= speed;
			if (tempPos.widthX == -frame.Width()) { tempPos.widthX = 0; }
			if (tempPos.widthX < 0)
				tempExtraPos = { tempPos.widthX + VIZ.GetScreenWidth(), tempPos.heightY };
		}
		else
		{
			direction = EDirection::EStill;
		}
		if (controllerData.isAttached)
		{
			if (controllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X] < -HK_GAMEPAD_LEFT_THUMB_DEADZONE)
			{
				direction = EDirection::ERight;
				tempExtraPos.widthX++;
				if (tempPos.widthX == frame.Width()) { tempPos.widthX = 0; }
				if (tempPos.widthX > 0)
					tempExtraPos = { tempPos.widthX - frame.Width(), tempPos.heightY }; //left
			}
			if (controllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X] > HK_GAMEPAD_LEFT_THUMB_DEADZONE)
			{
				direction = EDirection::ELeft;
				tempExtraPos.widthX--;
				if (tempPos.widthX == -frame.Width()) { tempPos.widthX = 0; }
				if (tempPos.widthX < 0)
					tempExtraPos = { tempPos.widthX + frame.Width(), tempPos.heightY }; //right
			}
		}
		SetPosition(tempPos);
		SetExtraBgPos(tempExtraPos);
	}
	else
	{
		direction = EDirection::EStill;
		SetExtraBgPos(tempExtraPos);
	}	
}