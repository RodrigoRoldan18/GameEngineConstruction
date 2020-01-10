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
private:
	vector2<int> position{ 0,0 };
	vector2<int> oldPos{ 0,0 };

protected:	
	int health{100};
	int damage{10};
	int speed{ 1 };
	std::string gfxName;
	ERole role{ERole::ENeutral};
	bool isAlive{ true };
	int animationFrames{ 0 };
	int currentAnimFrame{ 0 };
	EDirection direction{ EDirection::EStill };
	Rectangle frame;

public:
	Entity(const std::string& name) : gfxName(name) {};
	virtual ~Entity() = default;

	virtual void Update(const float s) = 0;
	virtual void InputHandling() = 0;

	void Render(const float s);
	void CheckCollision(Entity& other);
	bool CanCollideWith(const ERole& role, const ERole& other);
	void TakeDamage(const int& argDamage);
	void Movement();
	void CheckOffScreen();

	virtual void MoveTowardsPlayer(const std::vector<Entity*>& entityVector) {};

	void SetAliveStatus(const bool& argAliveStatus) { isAlive = argAliveStatus; }
	void SetPosition(const vector2<int>& argCasterPosition) { oldPos = position; position = argCasterPosition; }
	void SetDirection(const EDirection& argCasterDirection) { direction = argCasterDirection; }
	void SetRole(const ERole& argCasterRole) { role = argCasterRole; }
	void SetHealth(const int argHealth) { health = argHealth; }

	Rectangle GetFrame() const { return frame; }
	int GetDamage() const { return damage; }
	bool CheckIfAlive() const { return isAlive; }
	const std::string& GetName() const { return gfxName; }
	ERole GetRole() const { return role; }
	vector2<int> GetPosition() const { return position; }
	int GetHealth() const { return health; }
};

