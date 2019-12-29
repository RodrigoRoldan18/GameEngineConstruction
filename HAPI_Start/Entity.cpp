#include "Entity.h"
#include "Visualisation.h"

void Entity::CheckCollision(Entity& other)
{
	if (!CheckIfAlive() || !other.CheckIfAlive())
		return;
	if (!CanCollideWith(GetRole(), other.GetRole()))
		return;

	Rectangle thisRect{ VIZ.GetRect(GetName()) };

	int width{ thisRect.Width() };
	int height{ thisRect.Height() };

	thisRect.left += width / 10;
	thisRect.right -= width / 10;
	thisRect.top += height / 10;
	thisRect.bottom -= height / 10;

	Rectangle otherRect{ VIZ.GetRect(other.GetName()) };

	thisRect.Translate(GetPosition().widthX, GetPosition().heightY);
	otherRect.Translate(other.GetPosition().widthX, other.GetPosition().heightY);

	if (!thisRect.CompletelyOutside(otherRect))
	{
		//collision occured
		//potentially add pixel perfect collision
		TakeDamage(other.GetDamage());
		other.TakeDamage(GetDamage());
	}
}

bool Entity::CanCollideWith(const ERole& role, const ERole& other)
{
	if (role == ERole::EPlayer && other == ERole::EEnemy)
		return true;
	else if (role == ERole::EEnemy && other == ERole::EPlayer)
		return true;
	else
		return false;
}

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