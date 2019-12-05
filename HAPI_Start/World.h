#pragma once
#include <HAPI_lib.h>
#include <vector>
#include "Vector2.h"

class Visualisation;
class Entity;
enum class EDirection;
enum class ERole;

// HAPI itself is wrapped in the HAPISPACE namespace
using namespace HAPISPACE;

class World
{
private:
	std::shared_ptr<Visualisation> m_viz;
	std::vector<Entity*> m_entities;
	bool isFinished{ false };

public:
	World() {};
	~World();
	bool Initialisation();
	void Update();
	bool LoadLevel();
	void PoolOfBulletsAndExplosions();
	void Attack(const vector2<int>& argCasterPosition, const EDirection& argCasterDirection, const ERole& argCasterRole);

};

