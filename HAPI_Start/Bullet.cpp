#include "Bullet.h"
#include "Visualisation.h"

void Bullet::Update(const Visualisation& viz)
{
	viz.DrawSprite(gfxName, position, currentAnimFrame, frame);
}

void Bullet::InputHandling()
{
}

bool Bullet::HasCollided(const std::vector<Entity*>& m_entities, const Visualisation& viz)
{
	if (position.widthX < -frame.Width() || position.heightY < -frame.Width() || position.widthX > viz.GetScreenWidth() + frame.Width() || position.heightY > viz.GetScreenHeight() + frame.Height())
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
