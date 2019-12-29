#pragma once
#include "Entity.h"

class Enemy : public Entity
{
private:

public:
	Enemy(const std::string& name);
	void Update(const float s) override final;
	void InputHandling() override final;
};

