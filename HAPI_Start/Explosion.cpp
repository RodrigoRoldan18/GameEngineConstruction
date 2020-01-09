#include "Explosion.h"
#include "Visualisation.h"

Explosion::Explosion(const std::string& name) : Entity(name)
{
	frame = Rectangle(0, 64, 0, 64);
	role = ERole::ENeutral;
	isAlive = false;
	health = 1;
	speed = 0;
	animationFrames = 9;
	direction = EDirection::EStill;
}

void Explosion::Update(const float s)
{
	Render(s);
	currentAnimFrame++;
	if (currentAnimFrame == animationFrames)
	{ 
		currentAnimFrame = 0; 
		isAlive = false;
	}
}

void Explosion::InputHandling()
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
