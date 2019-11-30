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

bool Player::HasCollided(const std::vector<Entity*>& m_entities)
{
	for (auto& entity : m_entities)
	{
		if (entity->GetSide() == ERole::EEnemy)
		{
			if ((position.widthX * frame.right < entity->GetPosition().widthX * entity->GetFrame().left || position.widthX * frame.right > entity->GetPosition().widthX * entity->GetFrame().right)
				|| (position.heightY * frame.bottom < entity->GetPosition().heightY * entity->GetFrame().top || position.heightY * frame.bottom > entity->GetPosition().heightY * entity->GetFrame().bottom))
				return false;
			else
			{
				HAPI.RenderText(10, 60, HAPI_TColour::YELLOW, "Player is colliding with something", 14, HAPI_TextStyle::eRegular);
			}
		}
	}
	return false;
}

void Player::TakeDamage()
{
}
