#include "Enemy.h"
#include "Visualisation.h"
#include "World.h"
#include <time.h>

Enemy::Enemy(const std::string& name) : Entity(name)
{ 
	srand(time(0));
	if (rand() % 2 == 0)
		AI = EType::EPatroller;
	else
		AI = EType::ETracker;

	role = ERole::EEnemy;
	frame = Rectangle(0, 64, 0, 64); 
	direction = EDirection::ERight;

	if (AI == EType::EPatroller)
		SetPosition(vector2<int>(rand() % (VIZ.GetScreenWidth() - 100) + 50, 100));
	else
		SetPosition(vector2<int>(rand() % (VIZ.GetScreenWidth() - 100) + 50, rand() % (VIZ.GetScreenHeight() - 200) + 50));

}

Enemy::Enemy(const std::string& name, const vector2<int> Pos) : Entity(name)
{
	//this is for the spare ones
	srand(time(0));
	if (rand() % 2 == 0)
		AI = EType::EPatroller;
	else
		AI = EType::ETracker;

	role = ERole::EEnemy;
	frame = Rectangle(0, 64, 0, 64);
	direction = EDirection::ERight;
	isAlive = false;

	SetPosition(Pos);
}

void Enemy::Update(const float s)
{
	Render(s);
	if (firingCooldown > 0) { firingCooldown--; }
}

void Enemy::InputHandling()
{
	//this is allowed to run even if the enemies are dead to spawn and despawn them
	vector2<int> tempPos = GetPosition();

	const HAPI_TKeyboardData& keyboardData = HAPI.GetKeyboardData();
	const HAPI_TControllerData& controllerData = HAPI.GetControllerData(0);

	if (WORLD.isBgMoving())
	{
		if (keyboardData.scanCode['A'])
		{
			tempPos.widthX += speed * 2;
		}
		else if (keyboardData.scanCode['D'])
		{			
			tempPos.widthX -= speed * 2;
		}
		if (controllerData.isAttached)
		{
			if (controllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X] < -HK_GAMEPAD_LEFT_THUMB_DEADZONE)
			{
				tempPos.widthX += speed * 2;
			}
			if (controllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X] > HK_GAMEPAD_LEFT_THUMB_DEADZONE)
			{
				tempPos.widthX -= speed * 2;
			}
		}
		SetPosition(tempPos);
		//if it is completely outside of the screen on the left or completely about to enter on the right, then set to not alive or alive respectively
		SpawnDespawn();
	}	
}

void Enemy::SpawnDespawn()
{
	vector2<int> tempPos = GetPosition();
	if (tempPos.widthX < -frame.Width())// completely outside on the right
	{
		//Despawn offscreen
		isAlive = false;
		health = 100;
		if (rand() % 2 == 0)
			AI = EType::EPatroller;
		else
			AI = EType::ETracker;
		tempPos = vector2<int>(rand() % (VIZ.GetScreenWidth() / 3) + VIZ.GetScreenWidth(), rand() % (VIZ.GetScreenHeight() - 100) + 50);
		SetPosition(tempPos);
	}
	else if (tempPos.widthX > VIZ.GetScreenWidth() && tempPos.widthX < VIZ.GetScreenWidth() + 10)
	{
		//Spawn offscreen
		isAlive = true;
	}
	else if (tempPos.widthX > 0 && tempPos.widthX < VIZ.GetScreenWidth() - frame.Width() && !isAlive)
	{
		//Despawn onscreen
		isAlive = false;
		health = 100;
		if (rand() % 2 == 0)
			AI = EType::EPatroller;
		else
			AI = EType::ETracker;
		tempPos = vector2<int>(rand() % (VIZ.GetScreenWidth() / 3) + VIZ.GetScreenWidth(), rand() % (VIZ.GetScreenHeight() - 100) + 50);
		SetPosition(tempPos);
	}
}

void Enemy::MoveTowardsPlayer(const std::vector<Entity*>& entityVector)
{
	if (!CheckIfAlive())
		return;
	vector2<int> tempThisPos = GetPosition();

	switch (AI)
	{
	case Enemy::EType::ETracker:
		vector2<int> tempPlayerPos;
		for (Entity* object : entityVector)
		{
			if (object->CheckIfAlive() && object->GetRole() == ERole::EPlayer)
			{
				//object is the player
				tempPlayerPos = object->GetPosition();
				break;
			}
		}
		vector2<int> distance = tempThisPos - tempPlayerPos;
		if (distance.widthX < 0) { distance.widthX = -distance.widthX; }
		if (distance.heightY < 0) { distance.heightY = -distance.heightY; }
		if (distance.widthX > distance.heightY)
		{
			if (tempPlayerPos.widthX > tempThisPos.widthX)
				direction = EDirection::ERight;
			else
				direction = EDirection::ELeft;
		}
		else
		{
			if (tempPlayerPos.heightY > tempThisPos.heightY)
				direction = EDirection::EDown;
			else
				direction = EDirection::EUp;
		}
		if (firingCooldown == 0)
		{
			WORLD.FireBullet(tempThisPos, direction, role);
			firingCooldown = 50;
		}
		break;
	case Enemy::EType::EPatroller:
		if (tempThisPos.widthX < -frame.Width() / 2 && direction == EDirection::ELeft)
			direction = EDirection::ERight;
		else if (tempThisPos.widthX > VIZ.GetScreenWidth() - (frame.Width() / 2) && direction == EDirection::ERight)
			direction = EDirection::ELeft;
		if (firingCooldown == 0)
		{
			WORLD.FireBullet(tempThisPos, EDirection::EDown, role);
			firingCooldown = 50;
		}
		break;
	default:
		break;
	}
}