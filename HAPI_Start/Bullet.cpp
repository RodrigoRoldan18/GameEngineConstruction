#include "Bullet.h"
#include "Visualisation.h"

Bullet::Bullet(const std::string& name) : Entity(name) 
{
	frame = Rectangle(0, 32, 0, 32);
	isAlive = false;
	health = 1; 
	speed = 10;
}

void Bullet::Update()
{
	VIZ.DrawSprite(gfxName, position, currentAnimFrame, frame);
}

void Bullet::InputHandling()
{
	const HAPI_TKeyboardData& keyboardData = HAPI.GetKeyboardData();
	const HAPI_TControllerData& controllerData = HAPI.GetControllerData(0);
	if (keyboardData.scanCode['A'])
		position.widthX++;
	else if (keyboardData.scanCode['D'])
		position.widthX--;
	if (controllerData.isAttached)
	{
		if (controllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X] < -HK_GAMEPAD_LEFT_THUMB_DEADZONE)
			position.widthX++;

		else if (controllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X] > HK_GAMEPAD_LEFT_THUMB_DEADZONE)
			position.widthX--;
	}
}

bool Bullet::HasCollided(const Entity& entity)
{
	if (position.widthX < -frame.Width() || position.heightY < -frame.Width() || position.widthX > VIZ.GetScreenWidth() + frame.Width() || position.heightY > VIZ.GetScreenHeight() + frame.Height())
	{
		isAlive = false;
		return true;
	}
	else
	{
		if (role == ERole::EPlayer)
		{
			if (entity.GetRole() == ERole::EEnemy)
			{
				if (position.widthX < entity.GetPosition().widthX - entity.GetFrame().Width() / 1.5 ||
					position.heightY < entity.GetPosition().heightY - entity.GetFrame().Height() / 1.5 ||
					position.widthX > entity.GetPosition().widthX + entity.GetFrame().Width() / 1.5 ||
					position.heightY > entity.GetPosition().heightY + entity.GetFrame().Height() / 1.5)
					return false;
				else				
					return true;				
			}
		}
		else if (role == ERole::EEnemy)
		{
			if (entity.GetRole() == ERole::EPlayer)
			{
				if (position.widthX < entity.GetPosition().widthX - entity.GetFrame().Width() / 1.5 ||
					position.heightY < entity.GetPosition().heightY - entity.GetFrame().Height() / 1.5 ||
					position.widthX > entity.GetPosition().widthX + entity.GetFrame().Width() / 1.5 ||
					position.heightY > entity.GetPosition().heightY + entity.GetFrame().Height() / 1.5)
					return false;
				else				
					return true;				
			}
		}
		return false;
	}
}
