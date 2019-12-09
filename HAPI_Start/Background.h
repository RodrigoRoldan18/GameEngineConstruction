#pragma once
#include "Entity.h"

class Background : public Entity
{
private:
	vector2<int> extraBgPos;

public:
	Background(const std::string& name) : Entity(name) {frame = Rectangle(0, 1280, 0, 640); }
	void Update() override final;
	void InputHandling() override final;
	bool HasCollided(const std::vector<Entity*>& m_entities) override final;
	void TakeDamage(const int& argDamage) override final;
};

