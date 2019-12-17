#include "Enemy.h"
#include "Visualisation.h"

Enemy::Enemy(const std::string& name) : Entity(name)
{ 
	role = ERole::EEnemy;
	frame = Rectangle(0, 64, 0, 64); 
	direction = EDirection::ERight;
}

void Enemy::Update()
{
	VIZ.DrawSprite(gfxName, position, currentAnimFrame, frame);
}

void Enemy::InputHandling()
{
	if (position.widthX < -frame.Width() / 2 && direction == EDirection::ELeft)
		direction = EDirection::ERight;
	else if (position.widthX > VIZ.GetScreenWidth() - (frame.Width() / 2) && direction == EDirection::ERight)
		direction = EDirection::ELeft;
}

bool Enemy::HasCollided(const Entity& entity)
{
	if (entity.GetRole() == ERole::EPlayer)
	{
		if (position.widthX < entity.GetPosition().widthX - entity.GetFrame().Width() / 1.5 ||
			position.heightY < entity.GetPosition().heightY - entity.GetFrame().Height() / 1.5 ||
			position.widthX > entity.GetPosition().widthX + entity.GetFrame().Width() / 1.5 ||
			position.heightY > entity.GetPosition().heightY + entity.GetFrame().Height() / 1.5)
			return false;
		else
		{
			HAPI.RenderText(10, 80, HAPI_TColour::RED, "Enemy is colliding with something", 14, HAPI_TextStyle::eRegular);
			return true;
		}
	}
	return false;
}