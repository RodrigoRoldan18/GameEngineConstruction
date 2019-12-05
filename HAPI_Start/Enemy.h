#pragma once
#include "Entity.h"

class Enemy : public Entity
{
private:

public:
	Enemy(const std::string& name) : Entity(name) { role = ERole::EEnemy; frame = Rectangle(0, 64, 0, 64); }
	void Update(const Visualisation& viz) override final;
	void InputHandling() override final;
	bool HasCollided(const std::vector<Entity*>& m_entities, const Visualisation& viz) override final;
	void TakeDamage(const int& argDamage) override final;
};
