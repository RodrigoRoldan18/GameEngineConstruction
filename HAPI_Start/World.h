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

public:
	World() {};
	~World();
	bool Initialisation();
	void Update();
	bool LoadLevel();

};

