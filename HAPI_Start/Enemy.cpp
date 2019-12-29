#include "Enemy.h"
#include "Visualisation.h"

Enemy::Enemy(const std::string& name) : Entity(name)
{ 
	role = ERole::EEnemy;
	frame = Rectangle(0, 64, 0, 64); 
	direction = EDirection::ERight;
}

void Enemy::Update(const float s)
{
	VIZ.DrawSprite(gfxName, position, currentAnimFrame, frame);
	HAPI.RenderText(10, 60, HAPI_TColour::YELLOW, std::to_string(health), 14, HAPI_TextStyle::eRegular);
}

void Enemy::InputHandling()
{
	if (position.widthX < -frame.Width() / 2 && direction == EDirection::ELeft)
		direction = EDirection::ERight;
	else if (position.widthX > VIZ.GetScreenWidth() - (frame.Width() / 2) && direction == EDirection::ERight)
		direction = EDirection::ELeft;
}