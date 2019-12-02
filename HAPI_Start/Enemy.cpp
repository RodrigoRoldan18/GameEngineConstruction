#include "Enemy.h"
#include "Visualisation.h"

void Enemy::Update(const Visualisation& viz)
{
	viz.DrawSprite(gfxName, position, currentAnimFrame, frame);
}

void Enemy::InputHandling()
{
}

bool Enemy::HasCollided(const std::vector<Entity*>& m_entities, const Visualisation& viz)
{
	return false;
}

void Enemy::TakeDamage()
{
}
