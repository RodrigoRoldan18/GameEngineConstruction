#include "Player.h"
#include "Visualisation.h"
#include "World.h"

Player::Player(const std::string& name) : Entity(name)
{
	animationFrames = 23;
	role = ERole::EPlayer;
	frame = Rectangle(0, 64, 0, 64);
	SetPosition({ 0, 704 });
	speed = 4;
}

void Player::Update(const float s)
{
	Render(s);
	currentAnimFrame++;
	if (currentAnimFrame == animationFrames) { currentAnimFrame = 0; }
	if (firingCooldown > 0) { firingCooldown--; }
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
	{
		tempDirection = EDirection::ELeft;
		WORLD.SetMoveBackground(false);
	}
	else if (keyboardData.scanCode['S'] && tempPos.heightY < VIZ.GetScreenHeight() - frame.Height())
		tempDirection = EDirection::EDown;
	else if (keyboardData.scanCode['D'] && tempPos.widthX < VIZ.GetScreenWidth() - frame.Width())
	{
		tempDirection = EDirection::ERight;
		if (tempPos.widthX >= VIZ.GetScreenWidth() / 2) 
		{ 
			speed = 0; 
			WORLD.SetMoveBackground(true); 
		}
	}
	else
		tempDirection = EDirection::EStill;
	if (keyboardData.scanCode['E'] && firingCooldown == 0)
	{
		if (direction == EDirection::EStill) { WORLD.FireBullet(tempPos, previousDir, role); }
		else { WORLD.FireBullet(tempPos, direction, role); }
		firingCooldown = 10;
	}

	if (keyboardData.scanCode[HK_SPACE])
	{
		smoothJump = 10;
		tempPos.heightY -= smoothJump;
		/*HAPI_TSoundOptions options;
		options.volume = 0.3f;
		HAPI.PlaySound("Data\\JumpSound.wav", options);*/
	}
	else
	{
		if (smoothJump > 0)
		{
			tempPos.heightY -= smoothJump;
			smoothJump--;
		}
		else
		{
			//apply gravity
			if (tempPos.heightY < 704)
			{
				tempPos.heightY -= smoothJump;	//smooth jump will be negative
				if(smoothJump > -10)
					smoothJump--;
			}
		}		
	}

	if (controllerData.isAttached)
	{
		if (controllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y] > HK_GAMEPAD_LEFT_THUMB_DEADZONE && tempPos.heightY > 0)
			tempDirection = EDirection::EUp;
		else if (controllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X] < -HK_GAMEPAD_LEFT_THUMB_DEADZONE && tempPos.widthX > 0)
		{
			tempDirection = EDirection::ELeft;
			WORLD.SetMoveBackground(false);
		}
		else if (controllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y] < -HK_GAMEPAD_LEFT_THUMB_DEADZONE && tempPos.heightY < VIZ.GetScreenHeight())
			tempDirection = EDirection::EDown;
		else if (controllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X] > HK_GAMEPAD_LEFT_THUMB_DEADZONE && tempPos.widthX < VIZ.GetScreenWidth())
		{
			tempDirection = EDirection::ERight;
			if (tempPos.widthX >= VIZ.GetScreenWidth() / 2)
			{
				speed = 0;
				WORLD.SetMoveBackground(true);
			}
		}
		if (controllerData.analogueButtons[HK_ANALOGUE_RIGHT_TRIGGER] > HK_GAMEPAD_TRIGGER_THRESHOLD && firingCooldown == 0)
		{
			if (direction == EDirection::EStill) { WORLD.FireBullet(tempPos, previousDir, role); }
			else { WORLD.FireBullet(tempPos, direction, role); }
			firingCooldown = 10;
		}

		if (controllerData.digitalButtons[HK_DIGITAL_A])
		{
			smoothJump = 10;
			tempPos.heightY -= smoothJump;
			/*HAPI_TSoundOptions options;
			options.volume = 0.3f;
			HAPI.PlaySound("Data\\JumpSound.wav", options);*/
		}
		else
		{
			if (smoothJump > 0)
			{
				tempPos.heightY -= smoothJump;
				smoothJump--;
			}
			else
			{
				//apply gravity
				if (tempPos.heightY < 704)
				{
					tempPos.heightY -= smoothJump;	//smooth jump will be negative
					if (smoothJump > -10)
						smoothJump--;
				}
			}
		}
	}
	if (tempDirection != direction)
	{
		previousDir = direction;
		direction = tempDirection;
	}
	SetPosition(tempPos);
}