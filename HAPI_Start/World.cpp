#include "World.h"
#include "Visualisation.h"
#include "Player.h"
#include "Background.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Entity.h"
#include "Explosion.h"

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
	LoadPools();
	if (!LoadLevel())
		return false;
	if (!LoadSounds())
		return false;
	return true;
}

constexpr DWORD kTickTime{ 50 };

void World::Update()
{
	HAPI_TSoundOptions options;
	options.volume = 0.3f;
	options.loop = true;
	int instanceID{ 0 };
	HAPI.PlaySound("Data\\backgroundMusic.wav", options, instanceID);
	DWORD lastTimeTicked{ 0 };

	while (HAPI.Update())
	{		
		DWORD timeSinceLastTick{ HAPI.GetTime() - lastTimeTicked };
		if (timeSinceLastTick >= kTickTime)
		{
			for (Entity* entity : m_entities)
			{
				entity->CheckOffScreen();
				if (entity->CheckIfAlive())
				{
					if (entity->GetRole() == ERole::EEnemy)
						entity->MoveTowardsPlayer(m_entities);
					entity->Movement();
				}			
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
		DisplayUI();
		if (m_gameState != EState::EGame)
		{
			HAPI.StopSound(instanceID);
			break;
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
	if (!VIZ.CreateSprite("Data\\explosion.png", "Explosion"))
	{
		HAPI.UserMessage("Couldn't load the texture for the Explosion", "Warning");
		return false;
	}
	return true;
}

void World::LoadPools()
{
	for (int i = 0; i < 1; i++)
	{
		m_entities.push_back(new Enemy("Enemy"));	//TODO: add more enemies when position randomisation is done
	}
	for (int i = 0; i < 20; i++)
	{
		m_entities.push_back(new Bullet("Bullet"));
	}
	for (int i = 0; i < 20; i++)
	{
		m_entities.push_back(new Explosion("Explosion"));
	}
}

bool World::LoadSounds()
{
	if (!HAPI.LoadSound("Data\\backgroundMusic.wav"))
	{
		HAPI.UserMessage("Couldn't load the sound for the background music", "Warning");
		return false;
	}
	if (!HAPI.LoadSound("Data\\laserSound.wav"))
	{
		HAPI.UserMessage("Couldn't load the sound for the laser", "Warning");
		return false;
	}
	if (!HAPI.LoadSound("Data\\explosionSound.wav"))
	{
		HAPI.UserMessage("Couldn't load the sound for the explosion", "Warning");
		return false;
	}
	if (!HAPI.LoadSound("Data\\JumpSound.wav"))
	{
		HAPI.UserMessage("Couldn't load the sound for the jump", "Warning");
		return false;
	}
	return true;
}

void World::FireBullet(const vector2<int>& argCasterPosition, const EDirection& argCasterDirection, const ERole& argCasterRole)
{
	for (Entity* bullet : m_entities)
	{
		if (!bullet->CheckIfAlive() && bullet->GetName() == "Bullet")
		{
			//this can be done in an initialise function
			bullet->SetPosition(argCasterPosition);
			bullet->SetDirection(argCasterDirection);
			bullet->SetRole(argCasterRole);
			bullet->SetAliveStatus(true);
			HAPI_TSoundOptions options;
			options.volume = 0.3f;
			HAPI.PlaySound("Data\\laserSound.wav", options);
			break;			
		}
	}	
}

void World::SpawnExplosion(const vector2<int>& argCasterPosition)
{
	for (Entity* explosion : m_entities)
	{
		if (!explosion->CheckIfAlive() && explosion->GetName() == "Explosion")
		{
			explosion->SetPosition(argCasterPosition);
			explosion->SetAliveStatus(true);
			HAPI_TSoundOptions options;
			options.volume = 0.3f;
			HAPI.PlaySound("Data\\explosionSound.wav", options);
			break;
		}
	}
}

void World::DisplayUI()
{
	HAPI.RenderText(VIZ.GetScreenWidth() / 2, 20, HAPI_TColour::WHITE, "Score: " + std::to_string(score), 20, HAPI_TextStyle::eBold);
	for (Entity* player : m_entities)
	{
		if (player->GetName() == "Player")
		{
			HAPI.RenderText(10, 20, HAPI_TColour::YELLOW, "Health: " + std::to_string(player->GetHealth()), 14, HAPI_TextStyle::eBold);
		}
	}
}

void World::DisplayMainMenu()
{
	const int noOfOptions{ 2 };
	int optionIndex{ 0 };
	bool holdingKey{ false };

	while (HAPI.Update())
	{
		const HAPI_TKeyboardData& keyboardData = HAPI.GetKeyboardData();
		const HAPI_TControllerData& controllerData = HAPI.GetControllerData(0);

		VIZ.ClearToColour(HAPI_TColour::BLACK);

		VIZ.DrawSprite("Background", { 0,0 }, 0, VIZ.GetRect("Background"));

		//Display the title!
		HAPI.RenderText(200, 40, HAPI_TColour::CYAN, "Laika the Space Dog", 50, HAPI_TextStyle::eBold);

		if (optionIndex == 0)
		{
			//Display start game (this is also the current selected option)
			HAPI.RenderText(350, 200, HAPI_TColour::GREEN, HAPI_TColour::WHITE, 2.0f, "Start Game", 30, HAPI_TextStyle::eBold);

			//Display exit
			HAPI.RenderText(360, 300, HAPI_TColour::GREEN, "Exit Game", 30, HAPI_TextStyle::eBold);
		}
		else
		{
			//Display start game (this is also the current selected option)
			HAPI.RenderText(350, 200, HAPI_TColour::GREEN, "Start Game", 30, HAPI_TextStyle::eBold);

			//Display exit
			HAPI.RenderText(360, 300, HAPI_TColour::GREEN, HAPI_TColour::WHITE, 2.0f, "Exit Game", 30, HAPI_TextStyle::eBold);
		}

		if (keyboardData.scanCode['W'] && !holdingKey)
		{
			if (optionIndex == 0)
				optionIndex = 1;
			else
				optionIndex = 0;
			holdingKey = true;
		}
		else if (keyboardData.scanCode['S'] && !holdingKey)
		{
			if (optionIndex == 0)
				optionIndex = 1;
			else
				optionIndex = 0;
			holdingKey = true;
		}
		else if (keyboardData.scanCode[HK_SPACE])
		{
			if (optionIndex == 0)
			{
				m_gameState = EState::EGame;
				break;
			}
			else
			{
				endGame = true;
				break;
			}
		}
		else
		{
			holdingKey = false;
		}
		if (controllerData.isAttached)
		{
			if (controllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y] > HK_GAMEPAD_LEFT_THUMB_DEADZONE && !holdingKey)
			{
				if (optionIndex == 0)
					optionIndex = 1;
				else
					optionIndex = 0;
				holdingKey = true;
			}
			else if (controllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y] < -HK_GAMEPAD_LEFT_THUMB_DEADZONE && !holdingKey)
			{
				if (optionIndex == 0)
					optionIndex = 1;
				else
					optionIndex = 0;
				holdingKey = true;
			}
			else if (controllerData.digitalButtons[HK_DIGITAL_A])
			{
				if (optionIndex == 0)
				{
					m_gameState = EState::EGame;
					break;
				}
				else
				{
					endGame = true;
					break;
				}
			}
		}
	}
}

bool World::DisplayGameOver()
{
	bool isPlayingAgain;
	int optionIndex{ 0 };
	bool holdingKey{ false };

	while (HAPI.Update())
	{
		const HAPI_TKeyboardData& keyboardData = HAPI.GetKeyboardData();
		const HAPI_TControllerData& controllerData = HAPI.GetControllerData(0);

		VIZ.ClearToColour(HAPI_TColour::BLACK);

		VIZ.DrawSprite("Background", { 0,0 }, 0, VIZ.GetRect("Background"));

		//Display the title!
		HAPI.RenderText(200, 40, HAPI_TColour::RED, "GAME OVER!", 50, HAPI_TextStyle::eBold);

		//Display the score
		HAPI.RenderText(200, 150, HAPI_TColour::CYAN, "Score: " + std::to_string(score), 50, HAPI_TextStyle::eBold);

		if (optionIndex == 0)
		{
			//Display start game (this is also the current selected option)
			HAPI.RenderText(350, 250, HAPI_TColour::GREEN, HAPI_TColour::WHITE, 2.0f, "Back to menu", 30, HAPI_TextStyle::eBold);

			//Display exit
			HAPI.RenderText(360, 350, HAPI_TColour::GREEN, "Exit Game", 30, HAPI_TextStyle::eBold);
		}
		else
		{
			//Display start game (this is also the current selected option)
			HAPI.RenderText(350, 250, HAPI_TColour::GREEN, "Back to menu", 30, HAPI_TextStyle::eBold);

			//Display exit
			HAPI.RenderText(360, 350, HAPI_TColour::GREEN, HAPI_TColour::WHITE, 2.0f, "Exit Game", 30, HAPI_TextStyle::eBold);
		}

		if (keyboardData.scanCode['W'] && !holdingKey)
		{
			if (optionIndex == 0)
				optionIndex = 1;
			else
				optionIndex = 0;
			holdingKey = true;
		}
		else if (keyboardData.scanCode['S'] && !holdingKey)
		{
			if (optionIndex == 0)
				optionIndex = 1;
			else
				optionIndex = 0;
			holdingKey = true;
		}
		else if (keyboardData.scanCode[HK_SPACE])
		{
			if (optionIndex == 0)
			{
				m_gameState = EState::EMenu;
				break;
			}
			else
			{
				return true;
			}
		}
		else
		{
			holdingKey = false;
		}
		if (controllerData.isAttached)
		{
			if (controllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y] > HK_GAMEPAD_LEFT_THUMB_DEADZONE && !holdingKey)
			{
				if (optionIndex == 0)
					optionIndex = 1;
				else
					optionIndex = 0;
				holdingKey = true;
			}
			else if (controllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y] < -HK_GAMEPAD_LEFT_THUMB_DEADZONE && !holdingKey)
			{
				if (optionIndex == 0)
					optionIndex = 1;
				else
					optionIndex = 0;
				holdingKey = true;
			}
			else if (controllerData.digitalButtons[HK_DIGITAL_A])
			{
				if (optionIndex == 0)
				{
					m_gameState = EState::EMenu;
					break;
				}
				else
				{
					return true;
				}
			}
		}
	}
	return false;
}

void World::CheckGameState()
{
	switch (m_gameState)
	{
	case EState::EMenu:
		DisplayMainMenu();
		break;
	case EState::EGame:
		Update();
		break;
	case EState::EGameOver:
		endGame = DisplayGameOver();
		break;
	default:
		break;
	}
}

/*TODO:
	3. More enemies
	4. System to respawn enemies (if they are on the left, place them on the right)
	4. Add platforms(optional)

	references
	https://freesound.org/people/sharesynth/sounds/341247/
	https://freesound.org/people/V-ktor/sounds/435413/
	https://freesound.org/people/sharesynth/sounds/344512/
	https://freesound.org/people/FoolBoyMedia/sounds/264295/
	http://kidscancode.org/blog/2016/09/pygame_shmup_part_10/
*/