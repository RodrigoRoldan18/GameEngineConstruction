#include "Background.h"
#include "Visualisation.h"

Background::Background(const std::string& name) : Entity(name) 
{
	frame = Rectangle(0, 960, 0, 960);
	speed = 4;
}

void Background::Update(const float s)
{
	VIZ.DrawSprite(gfxName, position,0, frame);
	VIZ.DrawSprite(gfxName, extraBgPos,0, frame);//extra
}

void Background::InputHandling()
{
	const HAPI_TKeyboardData& keyboardData = HAPI.GetKeyboardData();
	const HAPI_TControllerData& controllerData = HAPI.GetControllerData(0);
	if (keyboardData.scanCode['A'])
	{
		direction = EDirection::ERight;
		extraBgPos.widthX+=speed;
		if (position.widthX == frame.Width()) { position.widthX = 0; }
		if (position.widthX >= 0)
			extraBgPos = { position.widthX - VIZ.GetScreenWidth() , position.heightY };
	}
	else if (keyboardData.scanCode['D'])
	{
		direction = EDirection::ELeft;
		extraBgPos.widthX-=speed;
		if (position.widthX == -frame.Width()) { position.widthX = 0; }
		if (position.widthX <= 0)
			extraBgPos = { position.widthX + VIZ.GetScreenWidth(), position.heightY };
	}
	else
	{
		direction = EDirection::EStill;
	}
	if (controllerData.isAttached)
	{
		if (controllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X] < -15000)
		{
			direction = EDirection::ERight;
			extraBgPos.widthX++;
			if (position.widthX == frame.Width()) { position.widthX = 0; }
			if (position.widthX >= 0)
				extraBgPos = { position.widthX - frame.Width(), position.heightY }; //left
		}
		if (controllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X] > 15000)
		{
			direction = EDirection::ELeft;
			extraBgPos.widthX--;
			if (position.widthX == -frame.Width()) { position.widthX = 0; }
			if(position.widthX < 0)
				extraBgPos = { position.widthX + frame.Width(), position.heightY }; //right
		}
	}
}