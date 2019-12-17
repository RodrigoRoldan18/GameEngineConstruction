#pragma once
#include "Entity.h"

class Enemy : public Entity
{
private:

public:
	Enemy(const std::string& name);
	void Update() override final;
	void InputHandling() override final;
	bool HasCollided(const Entity& entity) override final;
};

