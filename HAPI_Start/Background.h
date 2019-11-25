#pragma once
#include "Entity.h"

class Background : public Entity
{
private:
	vector2<int> extraBgPos;

public:
	Background(const std::string& name) : Entity(name) { role = ERole::ENeutral; }
	void Update(const Visualisation& viz) override final;
	void InputHandling(const Visualisation& viz);
};

