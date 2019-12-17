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
	enum EState
	{
		EMenu,
		EGame,
		EGameOver
	};

	EState m_gameState{EState::EGame};
	std::vector<Entity*> m_entities;
	bool isFinished{ false };

	static World* instance;
	World() {};

public:	
	static World& GetInstance();
	~World();
	bool Initialisation();
	void Update();
	bool LoadLevel();
	void PoolOfBulletsAndExplosions();
	void FireBullet(const vector2<int>& argCasterPosition, const EDirection& argCasterDirection, const ERole& argCasterRole);

};

#define WORLD World::GetInstance()

