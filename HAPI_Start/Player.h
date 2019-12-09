#pragma once
#include "Entity.h"

class Player : public Entity
{
private:
	int firingCooldown{ 0 };
	EDirection previousDir{ EDirection::EStill };

public:
	Player(const std::string& name) : Entity(name) { role = ERole::EPlayer; frame = Rectangle(0, 64, 0, 64);  }
	void Update() override final;
	void InputHandling() override final;
	bool HasCollided(const std::vector<Entity*>& m_entities) override final;
	void TakeDamage(const int& argDamage) override final;
};

