#pragma once
#include <vector>
#include <string>
#include "Vector2.h"
#include "Rectangle.h"

enum class ERole
{
	ENeutral,
	EPlayer,
	EEnemy
};

enum class EDirection
{
	ELeft,
	ERight,
	EUp,
	EDown,
	EStill
};

class Visualisation;

class Entity
{
protected:
	vector2<int> position{0,0};
	int health{100};
	int damage{10};
	std::string gfxName;
	ERole role{ERole::ENeutral};
	bool isAlive{ false };
	int animationFrames{ 23 };
	int currentAnimFrame{ 0 };
	Rectangle frame;
	EDirection direction{ EDirection::EStill };

public:
	Entity(const std::string& name) : gfxName(name) {};
	virtual ~Entity() = default;
	//void Render(const Visualisation& viz);
	virtual void Update(const Visualisation& viz) = 0;
	virtual void InputHandling() = 0;
	virtual bool HasCollided(const std::vector<Entity*>& m_entities, const Visualisation& viz) = 0;
	virtual void TakeDamage() = 0;
	void Movement();

	ERole GetSide() const { return role; }
	Rectangle GetFrame() const { return frame; }
	vector2<int> GetPosition() const { return position; }

};

