#include "Player.h"
#include "Visualisation.h"

void Player::Update(const Visualisation& viz)
{
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
	if (keyboardData.scanCode['E'] && !isAttacking)
	{
		HAPI.RenderText(10, 90, HAPI_TColour::HORRID_PINK, "Player is FIRING", 14, HAPI_TextStyle::eRegular);
		isAttacking = true;
	}
	if (controllerData.isAttached)
	{
		if (controllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y] > HK_GAMEPAD_LEFT_THUMB_DEADZONE)
		{
			direction = EDirection::EUp;
		}
		else if (controllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X] < -HK_GAMEPAD_LEFT_THUMB_DEADZONE)
		{
			direction = EDirection::ELeft;
		}
		else if (controllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y] < -HK_GAMEPAD_LEFT_THUMB_DEADZONE)
		{
			direction = EDirection::EDown;
		}
		else if (controllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X] > HK_GAMEPAD_LEFT_THUMB_DEADZONE)
		{
			direction = EDirection::ERight;
		}
		if (controllerData.analogueButtons[HK_ANALOGUE_RIGHT_TRIGGER] > HK_GAMEPAD_TRIGGER_THRESHOLD && !isAttacking)
		{
			HAPI.RenderText(10, 90, HAPI_TColour::HORRID_PINK, "Player is FIRING", 14, HAPI_TextStyle::eRegular);
			isAttacking = true;
		}
	}
}

bool Player::HasCollided(const std::vector<Entity*>& m_entities, const Visualisation& viz)
{
	for (auto& entity : m_entities)	//potentially move all collision to the sprite as it has the texture and rectangle.
	{
		if (entity->GetRole() == ERole::EEnemy)
		{
			if (position.widthX < entity->GetPosition().widthX - entity->GetFrame().Width() / 1.5 ||
				position.heightY < entity->GetPosition().heightY - entity->GetFrame().Height() / 1.5||
				position.widthX > entity->GetPosition().widthX + entity->GetFrame().Width() / 1.5 ||
				position.heightY > entity->GetPosition().heightY + entity->GetFrame().Height() / 1.5)
				return false;
			else
			{
				HAPI.RenderText(10, 60, HAPI_TColour::YELLOW, "Player is colliding with something", 14, HAPI_TextStyle::eRegular);
				//TakeDamage(entity->GetDamage());
				//entity->TakeDamage(damage);

				//PixelPerfectCollision
				//1. Create intersection rectangle
				//Rectangle intersection;
				//viz.PixelPerfectCollision(gfxName, position, entity->gfxName, entity->GetPosition());	//potentially move all collision to the sprite as it has the texture and rectangle
				//2. Loop through each pixel inside the intersection rectangle
				//3. compare to the offset of entity1 and 2
				//4. if both alphas are true then collision!

				//things to get: sprite for each
				return true;
			}
		}
	}
	return false;
}

void Player::TakeDamage(const int& argDamage)
{
	health -= argDamage;
	if (health <= 0)
		isAlive = false;
}
