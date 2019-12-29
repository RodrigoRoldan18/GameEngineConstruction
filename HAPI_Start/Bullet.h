#pragma once
#include "Entity.h"
#include "Vector2.h"

class Bullet : public Entity
{
public:
	Bullet(const std::string& name);
	void Update(const float s) override final;
	void InputHandling() override final;
};

