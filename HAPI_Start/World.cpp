#include "World.h"
#include "Visualisation.h"
#include "Player.h"
#include "Background.h"

World::~World()
{
	for (auto& entity : m_entities)
	{
		delete entity;
	}
}

bool World::Initialisation()
{
	HAPI.SetShowFPS(true);
	m_viz = std::make_shared<Visualisation>();
	m_entities.push_back(new Background("Background"));
	m_entities.push_back(new Player("Player"));
	//CreatePoolOf...
	if (!LoadLevel())
		return false;
	return true;
}

void World::Update()
{
	while (HAPI.Update())
	{		
		m_viz->ClearToColour(HAPI_TColour::BLACK);
		for (auto& entity : m_entities)
		{
			entity->Update(*m_viz);
		}
	}
}

bool World::LoadLevel()
{
	if (!m_viz->CreateSprite("Data\\planetBg.png", "Background"))
	{
		HAPI.UserMessage("Couldn't load the texture for the Background", "Warning");
		return false;
	}
	if (!m_viz->CreateSprite("Data\\playerSprite.tga", "Player"))
	{
		HAPI.UserMessage("Couldn't load the texture for the Player", "Warning");
		return false;
	}
	return true;
}
