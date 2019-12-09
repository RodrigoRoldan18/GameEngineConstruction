#pragma once
#include "Entity.h"
#include "Vector2.h"

class Bullet : public Entity
{
public:
	Bullet(const std::string& name) : Entity(name) { frame = Rectangle(0, 32, 0, 32); isAlive = false; health = 1; }
	void Update() override final;
	void InputHandling() override final;
	bool HasCollided(const std::vector<Entity*>& m_entities) override final;
	void TakeDamage(const int& argDamage) override final;
};

