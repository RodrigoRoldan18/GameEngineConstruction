#include "Player.h"
#include "Visualisation.h"
#include "World.h"

Player::Player(const std::string& name) : Entity(name)
{
	role = ERole::EPlayer;
	frame = Rectangle(0, 64, 0, 64);
	position = { 0, 704 };
}

void Player::Update()
{
	VIZ.DrawSprite(gfxName, position, currentAnimFrame, frame);
	currentAnimFrame++;
	if (currentAnimFrame == animationFrames) { currentAnimFrame = 0; }
	if (firingCooldown > 0) { firingCooldown--; }

	//apply gravity
	if (position.heightY < 704)
	{
		position.heightY += 4;
	}
}

void Player::InputHandling()
{
	EDirection tempDirection = direction;
	const HAPI_TKeyboardData& keyboardData = HAPI.GetKeyboardData();
	const HAPI_TControllerData& controllerData = HAPI.GetControllerData(0);
	if (keyboardData.scanCode['W'] && position.heightY > 0)
		tempDirection = EDirection::EUp;
	else if (keyboardData.scanCode['A'] && position.widthX > 0)
		tempDirection = EDirection::ELeft;
	else if (keyboardData.scanCode['S'] && position.heightY < VIZ.GetScreenHeight() - frame.Height())
		tempDirection = EDirection::EDown;
	else if (keyboardData.scanCode['D'] && position.widthX < VIZ.GetScreenWidth() - frame.Width())
		tempDirection = EDirection::ERight;
	else
		tempDirection = EDirection::EStill;
	if (keyboardData.scanCode['E'] && firingCooldown == 0)
	{
		if (direction == EDirection::EStill) { WORLD.FireBullet(position, previousDir, role); }
		else { WORLD.FireBullet(position, direction, role); }
		firingCooldown = 20;
	}
	if (keyboardData.scanCode[HK_LSHIFT])
		speed = 5;
	else if (keyboardData.scanCode[HK_SPACE])
	{
		tempDirection = EDirection::EUp;
		speed = 20;
	}
	else
		speed = 2;
	if (controllerData.isAttached)
	{
		if (controllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y] > HK_GAMEPAD_LEFT_THUMB_DEADZONE && position.heightY > 0)
			tempDirection = EDirection::EUp;
		else if (controllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X] < -HK_GAMEPAD_LEFT_THUMB_DEADZONE && position.widthX > 0)
			tempDirection = EDirection::ELeft;
		else if (controllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y] < -HK_GAMEPAD_LEFT_THUMB_DEADZONE && position.heightY < VIZ.GetScreenHeight())
			tempDirection = EDirection::EDown;
		else if (controllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X] > HK_GAMEPAD_LEFT_THUMB_DEADZONE && position.widthX < VIZ.GetScreenWidth())
			tempDirection = EDirection::ERight;
		if (controllerData.analogueButtons[HK_ANALOGUE_RIGHT_TRIGGER] > HK_GAMEPAD_TRIGGER_THRESHOLD && firingCooldown == 0)
		{
			if (direction == EDirection::EStill) { WORLD.FireBullet(position, previousDir, role); }
			else { WORLD.FireBullet(position, direction, role); }
			firingCooldown = 20;
		}
	}
	if (tempDirection != direction)
	{
		previousDir = direction;
		direction = tempDirection;
	}
}

bool Player::HasCollided(const Entity& entity)
{
	if (entity.GetRole() == ERole::EEnemy)
	{
		if (position.widthX < entity.GetPosition().widthX - entity.GetFrame().Width() / 1.5 ||
			position.heightY < entity.GetPosition().heightY - entity.GetFrame().Height() / 1.5||
			position.widthX > entity.GetPosition().widthX + entity.GetFrame().Width() / 1.5 ||
			position.heightY > entity.GetPosition().heightY + entity.GetFrame().Height() / 1.5)
			return false;
		else
		{
			HAPI.RenderText(10, 60, HAPI_TColour::YELLOW, "Player is colliding with something", 14, HAPI_TextStyle::eRegular);
			//TakeDamage(entity->GetDamage());
			//entity->TakeDamage(damage);

			//PixelPerfectCollision
			//1. Create intersection rectangle
			//Rectangle intersection;
			//viz.PixelPerfectCollision(gfxName, position, entity->gfxName, entity->GetPosition());	//potentially move all collision to the sprite as it has the texture and rectangle
			//2. Loop through each pixel inside the intersection rectangle
			//3. compare to the offset of entity1 and 2
			//4. if both alphas are true then collision!

			//things to get: sprite for each
			return true;
		}
	}
	return false;
}