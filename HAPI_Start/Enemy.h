#pragma once
#include "Entity.h"

class Enemy : public Entity
{
private:
	enum class EType
	{
		ETracker,
		EPatroller
	};
	EType AI;
	int firingCooldown{ 0 };

public:
	Enemy(const std::string& name);
	Enemy(const std::string& name, const vector2<int> Pos);
	void Update(const float s) override final;
	void InputHandling() override final;
	void SpawnDespawn();
	void MoveTowardsPlayer(const std::vector<Entity*>& entityVector) override final;
};

