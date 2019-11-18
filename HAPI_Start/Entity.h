#pragma once
#include <string>
#include "Vector2.h"

enum class ERole
{
	ENeutral,
	EPlayer,
	EEnemy
};

class Entity
{
protected:
	vector2<int> position{0,0};
	int health{100};
	int damage{10};
	std::string gfxName;
	ERole role{ERole::ENeutral};
	bool isAlive{ false };

public:
	Entity(const std::string& name) : gfxName(name) {};
	virtual ~Entity() = default;
	virtual void Update() = 0;

};

