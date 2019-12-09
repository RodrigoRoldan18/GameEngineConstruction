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
	bool isAlive{ true };
	int animationFrames{ 23 };
	int currentAnimFrame{ 0 };
	Rectangle frame;
	EDirection direction{ EDirection::EStill };

public:
	Entity(const std::string& name) : gfxName(name) {};
	virtual ~Entity() = default;
	//void Render(const Visualisation& viz);
	virtual void Update() = 0;
	virtual void InputHandling() = 0;
	virtual bool HasCollided(const std::vector<Entity*>& m_entities) = 0;
	virtual void TakeDamage(const int& argDamage) = 0;
	void Movement();

	void SetAliveStatus(const bool& argAliveStatus) { isAlive = argAliveStatus; }
	void SetPosition(const vector2<int>& argCasterPosition) { position = argCasterPosition; }
	void SetDirection(const EDirection& argCasterDirection) { direction = argCasterDirection; }
	void SetRole(const ERole& argCasterRole) { role = argCasterRole; }

	Rectangle GetFrame() const { return frame; }
	int GetDamage() const { return damage; }
	bool CheckIfAlive() const { return isAlive; }
	const std::string& GetName() const { return gfxName; }
	ERole GetRole() const { return role; }
	vector2<int> GetPosition() const { return position; }
};

