#include "Bullet.h"
#include "Visualisation.h"

Bullet::Bullet(const std::string& name) : Entity(name) 
{
	frame = Rectangle(0, 32, 0, 32);
	isAlive = false;
	health = 1; 
	speed = 20;
}

void Bullet::Update(const float s)
{
	Render(s);
}

void Bullet::InputHandling()
{
	const HAPI_TKeyboardData& keyboardData = HAPI.GetKeyboardData();
	const HAPI_TControllerData& controllerData = HAPI.GetControllerData(0);

	vector2<int> tempPos{ GetPosition() };

	if (keyboardData.scanCode['A'])
		tempPos.widthX++;
	else if (keyboardData.scanCode['D'])
		tempPos.widthX--;
	if (controllerData.isAttached)
	{
		if (controllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X] < -HK_GAMEPAD_LEFT_THUMB_DEADZONE)
			tempPos.widthX++;

		else if (controllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X] > HK_GAMEPAD_LEFT_THUMB_DEADZONE)
			tempPos.widthX--;
	}
	SetPosition(tempPos);
}
