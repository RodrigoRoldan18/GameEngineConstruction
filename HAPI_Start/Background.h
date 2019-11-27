#pragma once
#include "Entity.h"

class Background : public Entity
{
private:
	vector2<int> extraBgPos;

public:
	Background(const std::string& name) : Entity(name) { role = ERole::ENeutral; frame = Rectangle(0, 1280, 0, 640); }
	void Update(const Visualisation& viz) override final;
	void InputHandling() override final;
};

