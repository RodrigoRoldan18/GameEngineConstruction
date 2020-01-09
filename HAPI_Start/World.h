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

enum class EState
{
	EMenu,
	EGame,
	EGameOver
};

class World
{
private:
	EState m_gameState{EState::EMenu};
	std::vector<Entity*> m_entities;
	bool endGame{ false };
	bool moveBackground{ false };

	int score{ 0 };

	static World* instance;
	World() = default;

public:	
	static World& GetInstance();
	~World();
	bool Initialisation();
	void Update();
	bool LoadLevel();
	void LoadPools();
	bool LoadSounds();
	void FireBullet(const vector2<int>& argCasterPosition, const EDirection& argCasterDirection, const ERole& argCasterRole);
	void SpawnExplosion(const vector2<int>& argCasterPosition);
	void DisplayUI();
	void DisplayMainMenu();
	bool DisplayGameOver();
	void CheckGameState();

	void SetMoveBackground(bool argBool) { moveBackground = argBool; }
	void AddToScore(const int objectValue) { score += objectValue; }
	void SetGameState(const EState& newState) { m_gameState = newState; }

	bool isBgMoving() const { return moveBackground; }
	bool isFinished() const { return endGame; }

};

#define WORLD World::GetInstance()

