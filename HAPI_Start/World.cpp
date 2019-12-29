#include "World.h"
#include "Visualisation.h"
#include "Player.h"
#include "Background.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Entity.h"

#include <cassert>

World* World::instance{ nullptr };

World& World::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new World();
	}
	return *instance;
}

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
	m_entities.push_back(new Background("Background"));
	m_entities.push_back(new Player("Player"));
	m_entities.push_back(new Enemy("Enemy"));
	PoolOfBulletsAndExplosions();
	if (!LoadLevel())
		return false;
	return true;
}

constexpr DWORD kTickTime{ 50 };

void World::Update()
{
	DWORD lastTimeTicked{ 0 };
	while (HAPI.Update())
	{		
		DWORD timeSinceLastTick{ HAPI.GetTime() - lastTimeTicked };
		if (timeSinceLastTick >= kTickTime)
		{
			for (Entity* entity : m_entities)
			{
				if (entity->CheckIfAlive())				
					entity->Movement();				
			}
			lastTimeTicked = HAPI.GetTime();
			for (size_t i = 0; i < m_entities.size(); i++)
			{
				for (size_t j = i + 1; j < m_entities.size(); j++)
				{					
					m_entities[i]->CheckCollision(*m_entities[j]);
				}
			}
			timeSinceLastTick = 0;
		}
		float s = timeSinceLastTick / (float)kTickTime;
		assert(s >= 0 && s <= 1.0f);

		VIZ.ClearToColour(HAPI_TColour::BLACK);
		for (Entity* entity : m_entities)
		{
			if (entity->CheckIfAlive())
				entity->Update(s);
		}
	}
}

bool World::LoadLevel()
{
	if (!VIZ.CreateSprite("Data\\square_bg.jfif", "Background"))
	{
		HAPI.UserMessage("Couldn't load the texture for the Background", "Warning");
		return false;
	}
	if (!VIZ.CreateSprite("Data\\dogstill.png", "Player"))
	{
		HAPI.UserMessage("Couldn't load the texture for the Player", "Warning");
		return false;
	}
	if (!VIZ.CreateSprite("Data\\playerSprite.tga", "Enemy"))
	{
		HAPI.UserMessage("Couldn't load the texture for the Enemy", "Warning");
		return false;
	}
	if (!VIZ.CreateSprite("Data\\energyBall.png", "Bullet"))
	{
		HAPI.UserMessage("Couldn't load the texture for the Bullet", "Warning");
		return false;
	}
	return true;
}

void World::PoolOfBulletsAndExplosions()
{
	for (int i = 0; i < 20; i++)
	{
		m_entities.push_back(new Bullet("Bullet"));
		//then add the explosions in here too.
	}
}

void World::FireBullet(const vector2<int>& argCasterPosition, const EDirection& argCasterDirection, const ERole& argCasterRole)
{
	for (Entity* bullet : m_entities)
	{
		if (!bullet->CheckIfAlive() && bullet->GetName() == "Bullet")
		{
			//this can be done in an initialise function
			bullet->SetAliveStatus(true);
			bullet->SetPosition(argCasterPosition);
			bullet->SetDirection(argCasterDirection);
			bullet->SetRole(argCasterRole);
			break;			
		}
	}	
}
