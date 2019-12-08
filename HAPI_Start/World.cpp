#include "World.h"
#include "Visualisation.h"
#include "Player.h"
#include "Background.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Entity.h"

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
	m_entities.push_back(new Enemy("Enemy"));
	PoolOfBulletsAndExplosions();
	if (!LoadLevel())
		return false;
	return true;
}

void World::Update()
{
	while (HAPI.Update())
	{		
		//masterTime = HAPI.GetTime();
		m_viz->ClearToColour(HAPI_TColour::BLACK);
		for (Entity* entity : m_entities)
		{
			if (entity->CheckIfAlive())
			{
				entity->Movement();				
				if (entity->CheckIfAttacking())
				{
					Attack(entity->GetPosition(), entity->GetDirection(), entity->GetRole());
					//entity->SetAttack(false);
				}								
				entity->Update(*m_viz);
				entity->HasCollided(m_entities, *m_viz);
			}
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
	if (!m_viz->CreateSprite("Data\\dogstill.png", "Player"))
	{
		HAPI.UserMessage("Couldn't load the texture for the Player", "Warning");
		return false;
	}
	if (!m_viz->CreateSprite("Data\\playerSprite.tga", "Enemy"))
	{
		HAPI.UserMessage("Couldn't load the texture for the Enemy", "Warning");
		return false;
	}
	if (!m_viz->CreateSprite("Data\\energyBall.png", "Bullet"))
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
			bullet->SetAliveStatus(true);
			bullet->SetPosition(argCasterPosition);
			bullet->SetDirection(argCasterDirection);
			bullet->SetRole(argCasterRole);
			break;			
		}
	}	
}
