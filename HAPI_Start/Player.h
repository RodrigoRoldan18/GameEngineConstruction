#pragma once
#include "Entity.h"

class Player : public Entity
{
private:
	int firingCooldown{ 0 };
	EDirection previousDir{ EDirection::EStill };

public:
	Player(const std::string& name);
	void Update() override final;
	void InputHandling() override final;
	bool HasCollided(const Entity& entity) override final;
};

