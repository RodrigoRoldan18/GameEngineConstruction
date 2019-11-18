#include "World.h"
#include "Visualisation.h"

World::World()
{
	HAPI.SetShowFPS(true);
	playerPos = { 0 , 100 };
	backgroundPos = { 0, 0 };
	m_viz = std::make_shared<Visualisation>();
}

World::~World()
{
	for (auto& entity : m_entities)
	{
		delete entity;
	}
}

void World::Update()
{
	while (HAPI.Update())
	{		
		m_viz->ClearToColour(HAPI_TColour::BLACK);
		m_viz->DrawSprite("Background", backgroundPos.widthX, backgroundPos.heightY);
		m_viz->DrawSprite("Background", backgroundPos.widthX - m_viz->GetScreenWidth(), backgroundPos.heightY);//left
		m_viz->DrawSprite("Background", backgroundPos.widthX + m_viz->GetScreenWidth(), backgroundPos.heightY);//right
		m_viz->DrawSprite("Player", playerPos.widthX, playerPos.heightY);
		InputHandling();
	}
}

void World::InputHandling()
{
	const HAPI_TKeyboardData& keyboardData = HAPI.GetKeyboardData();
	const HAPI_TControllerData& controllerData = HAPI.GetControllerData(0);
	if (controllerData.isAttached)
	{
		if (keyboardData.scanCode['W'] || controllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y] > 15000)
		{
			playerPos.heightY--;
		}
		if (keyboardData.scanCode['A'] || controllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X] < -15000)
		{
			playerPos.widthX--;
			backgroundPos.widthX++;
			if (backgroundPos.widthX == m_viz->GetScreenWidth()) { backgroundPos.widthX = 0; }
		}
		if (keyboardData.scanCode['S'] || controllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y] < -15000)
		{
			playerPos.heightY++;
		}
		if (keyboardData.scanCode['D'] || controllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X] > 15000)
		{
			playerPos.widthX++;
			backgroundPos.widthX--;
			if (backgroundPos.widthX == -m_viz->GetScreenWidth()) { backgroundPos.widthX = 0; }
		}
	}
}

void World::LoadLevel()
{
	if (!m_viz->CreateSprite("Data\\planetBg.png", "Background"))
	{
		HAPI.UserMessage("Couldn't load the texture for the Background", "Warning");
		return;
	}
	if (!m_viz->CreateSprite("Data\\playerSprite.tga", "Player"))
	{
		HAPI.UserMessage("Couldn't load the texture for the Player", "Warning");
		return;
	}
}
