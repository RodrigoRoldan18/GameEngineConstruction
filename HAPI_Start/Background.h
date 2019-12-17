#pragma once
#include "Entity.h"

class Background : public Entity
{
private:
	vector2<int> extraBgPos = position;

public:
	Background(const std::string& name);
	void Update() override final;
	void InputHandling() override final;
	bool HasCollided(const Entity& entity) override final;
};

