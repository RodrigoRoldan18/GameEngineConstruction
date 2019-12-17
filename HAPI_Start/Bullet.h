#pragma once
#include "Entity.h"
#include "Vector2.h"

class Bullet : public Entity
{
public:
	Bullet(const std::string& name);
	void Update() override final;
	void InputHandling() override final;
	bool HasCollided(const Entity& entity) override final;
};

