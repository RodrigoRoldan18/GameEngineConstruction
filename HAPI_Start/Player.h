#pragma once
#include "Entity.h"
class Player : public Entity
{
private:

public:
	Player(const std::string& name) : Entity(name) {};
	void Update() override final;

};

