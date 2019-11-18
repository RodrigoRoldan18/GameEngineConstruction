#pragma once
#include <HAPI_lib.h>
#include <vector>
#include "Vector2.h"

class Visualisation;
class Entity;

// HAPI itself is wrapped in the HAPISPACE namespace
using namespace HAPISPACE;

class World
{
private:
	std::shared_ptr<Visualisation> m_viz;
	std::vector<Entity*> m_entities;

	//these will be moved into Entity eventually
	vector2<int> playerPos{ 0 , 100 };
	vector2<int> backgroundPos{ 0, 0 };
public:
	World();
	~World();
	void Update();
	void InputHandling();
	void LoadLevel();

};

