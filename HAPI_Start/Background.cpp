#include "Background.h"
#include "Visualisation.h"

void Background::Update(const Visualisation& viz)
{
	viz.DrawSprite(gfxName, position,0, frame);
	viz.DrawSprite(gfxName, extraBgPos,0, frame);//extra
}

void Background::InputHandling()
{
	const HAPI_TKeyboardData& keyboardData = HAPI.GetKeyboardData();
	const HAPI_TControllerData& controllerData = HAPI.GetControllerData(0);
	if (keyboardData.scanCode['A'])
	{
		direction = EDirection::ERight;
		extraBgPos.widthX++;
		if (position.widthX == frame.Width()) { position.widthX = 0; }
		if (position.widthX > 0)
			extraBgPos = { position.widthX - frame.Width(), position.heightY };
	}
	else if (keyboardData.scanCode['D'])
	{
		direction = EDirection::ELeft;
		extraBgPos.widthX--;
		if (position.widthX == -frame.Width()) { position.widthX = 0; }
		if (position.widthX < 0)
			extraBgPos = { position.widthX + frame.Width(), position.heightY };
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
			if (position.widthX > 0)
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

bool Background::HasCollided(const std::vector<Entity*>& m_entities)
{
	return false;
}

void Background::TakeDamage()
{
}
