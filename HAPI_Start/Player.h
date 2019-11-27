#pragma once
#include "Entity.h"

class Player : public Entity
{
private:

public:
	Player(const std::string& name) : Entity(name) { role = ERole::EPlayer; frame = Rectangle(0, 64, 0, 64); }
	void Update(const Visualisation& viz) override final;
	void InputHandling() override final;
};

