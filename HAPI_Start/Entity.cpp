#include "Entity.h"
#include "Visualisation.h"
#include "World.h"

void Entity::Render(const float s)
{
	vector2<int> interPos{ oldPos + (position - oldPos) * s };
	VIZ.DrawSprite(gfxName, interPos, currentAnimFrame, frame);
}

void Entity::CheckCollision(Entity& other)
{
	if (!CheckIfAlive() || !other.CheckIfAlive())
		return;
	if (!CanCollideWith(GetRole(), other.GetRole()))
		return;

	Rectangle thisRect{ frame };

	int width{ thisRect.Width() };
	int height{ thisRect.Height() };

	thisRect.left += width / 15;
	thisRect.right -= width / 15;
	thisRect.top += height / 15;
	thisRect.bottom -= height / 15;

	Rectangle otherRect{ other.GetFrame() };

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
	if (GetName() == "Player")
	{
		//rumble the control
	}
	if (health <= 0)
	{
		if (GetName() == "Enemy")
		{
			WORLD.AddToScore(200); //lets put 200 as a value for the enemies for example
		}
		else if (GetName() == "Player")
			WORLD.SetGameState(EState::EGameOver);
		isAlive = false;
		WORLD.SpawnExplosion(GetPosition());
	}
}

void Entity::Movement()
{
	InputHandling();
	if (!CheckIfAlive())
		return;
	vector2<int>pos{ GetPosition() };
	switch (direction)
	{
	case EDirection::ELeft:
		pos.widthX -= speed;
		break;
	case EDirection::ERight:
		pos.widthX += speed;
		break;
	case EDirection::EUp:
		pos.heightY -= speed;
		break;
	case EDirection::EDown:
		pos.heightY += speed;
		break;
	case EDirection::EStill:
		break;
	default:
		break;
	}
	SetPosition(pos);
}

void Entity::CheckOffScreen()
{
	if (position.widthX < -frame.Width() || position.heightY < -frame.Width() || position.widthX > VIZ.GetScreenWidth() + frame.Width() || position.heightY > VIZ.GetScreenHeight() + frame.Height())
	{
		isAlive = false;
	}
}
