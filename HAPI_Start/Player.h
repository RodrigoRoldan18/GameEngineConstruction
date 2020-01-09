#pragma once
#include "Entity.h"

class Player : public Entity
{
private:
	int firingCooldown{ 0 };
	EDirection previousDir{ EDirection::EStill };
	int smoothJump{ 0 };

public:
	Player(const std::string& name);
	void Update(const float s) override final;
	void InputHandling() override final;
};

