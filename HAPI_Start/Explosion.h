#pragma once
#include "Entity.h"

class Explosion : public Entity
{
public:
	Explosion(const std::string& name);
	void Update(const float s) override final;
	void InputHandling() override final;
};

