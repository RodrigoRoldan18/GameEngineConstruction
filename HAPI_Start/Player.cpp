#include "Player.h"
#include "Visualisation.h"
#include "World.h"

Player::Player(const std::string& name) : Entity(name)
{
	role = ERole::EPlayer;
	frame = Rectangle(0, 64, 0, 64);
	SetPosition({ 0, 704 });
	speed = { 4 };
}

void Player::Update(const float s)
{
	vector2<int> interPos{ oldPos + (position - oldPos) * s };
	VIZ.DrawSprite(gfxName, interPos, currentAnimFrame, frame);
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
	vector2<int> tempPos{ GetPosition() };

	speed = 4;
	const HAPI_TKeyboardData& keyboardData = HAPI.GetKeyboardData();
	const HAPI_TControllerData& controllerData = HAPI.GetControllerData(0);
	if (keyboardData.scanCode['W'] && tempPos.heightY > 0)
		tempDirection = EDirection::EUp;
	else if (keyboardData.scanCode['A'] && tempPos.widthX > 0)
		tempDirection = EDirection::ELeft;
	else if (keyboardData.scanCode['S'] && tempPos.heightY < VIZ.GetScreenHeight() - frame.Height())
		tempDirection = EDirection::EDown;
	else if (keyboardData.scanCode['D'] && tempPos.widthX < VIZ.GetScreenWidth() - frame.Width())
	{
		tempDirection = EDirection::ERight;
		if (tempPos.widthX >= VIZ.GetScreenWidth() / 2) { speed = 0; }
	}
	else
		tempDirection = EDirection::EStill;
	if (keyboardData.scanCode['E'] && firingCooldown == 0)
	{
		if (direction == EDirection::EStill) { WORLD.FireBullet(tempPos, previousDir, role); }
		else { WORLD.FireBullet(tempPos, direction, role); }
		firingCooldown = 20;
	}
	if (keyboardData.scanCode[HK_SPACE])
	{
		tempPos.heightY -= 20;
	}
	if (controllerData.isAttached)
	{
		if (controllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y] > HK_GAMEPAD_LEFT_THUMB_DEADZONE && tempPos.heightY > 0)
			tempDirection = EDirection::EUp;
		else if (controllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X] < -HK_GAMEPAD_LEFT_THUMB_DEADZONE && tempPos.widthX > 0)
			tempDirection = EDirection::ELeft;
		else if (controllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y] < -HK_GAMEPAD_LEFT_THUMB_DEADZONE && tempPos.heightY < VIZ.GetScreenHeight())
			tempDirection = EDirection::EDown;
		else if (controllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X] > HK_GAMEPAD_LEFT_THUMB_DEADZONE && tempPos.widthX < VIZ.GetScreenWidth())
			tempDirection = EDirection::ERight;
		if (controllerData.analogueButtons[HK_ANALOGUE_RIGHT_TRIGGER] > HK_GAMEPAD_TRIGGER_THRESHOLD && firingCooldown == 0)
		{
			if (direction == EDirection::EStill) { WORLD.FireBullet(tempPos, previousDir, role); }
			else { WORLD.FireBullet(tempPos, direction, role); }
			firingCooldown = 20;
		}
		if (controllerData.digitalButtons[HK_DIGITAL_A])
			tempPos.heightY -= 20;
	}
	if (tempDirection != direction)
	{
		previousDir = direction;
		direction = tempDirection;
	}
	SetPosition(tempPos);
}