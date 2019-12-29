#pragma once
#include "Entity.h"

class Player : public Entity
{
private:
	int firingCooldown{ 0 };
	int score{ 0 };
	EDirection previousDir{ EDirection::EStill };

public:
	Player(const std::string& name);
	void Update(const float s) override final;
	void InputHandling() override final;
};

