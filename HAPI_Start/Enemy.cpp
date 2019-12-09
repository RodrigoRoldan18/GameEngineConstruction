#include "Enemy.h"
#include "Visualisation.h"

void Enemy::Update()
{
	VIZ.DrawSprite(gfxName, position, currentAnimFrame, frame);
}

void Enemy::InputHandling()
{
}

bool Enemy::HasCollided(const std::vector<Entity*>& m_entities)
{
	return false;
}

void Enemy::TakeDamage(const int& argDamage)
{
}
