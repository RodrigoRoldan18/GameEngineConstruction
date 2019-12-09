#include "Bullet.h"
#include "Visualisation.h"

void Bullet::Update()
{
	VIZ.DrawSprite(gfxName, position, currentAnimFrame, frame);
}

void Bullet::InputHandling()
{
}

bool Bullet::HasCollided(const std::vector<Entity*>& m_entities)
{
	if (position.widthX < -frame.Width() || position.heightY < -frame.Width() || position.widthX > VIZ.GetScreenWidth() + frame.Width() || position.heightY > VIZ.GetScreenHeight() + frame.Height())
	{
		isAlive = false;
		return true;
	}
	else
	{
		return false;
	}
}

void Bullet::TakeDamage(const int& argDamage)
{
}
