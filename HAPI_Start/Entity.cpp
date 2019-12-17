#include "Entity.h"

void Entity::TakeDamage(const int& argDamage)
{
	health -= argDamage;
	if (health <= 0)
		isAlive = false;
}

void Entity::Movement()
{
	InputHandling();
	switch (direction)
	{
	case EDirection::ELeft:
		position.widthX -= speed;
		break;
	case EDirection::ERight:
		position.widthX += speed;
		break;
	case EDirection::EUp:
		position.heightY -= speed;
		break;
	case EDirection::EDown:
		position.heightY += speed;
		break;
	case EDirection::EStill:
		break;
	default:
		break;
	}
}