#include "Entity.h"

//void Entity::Render(const Visualisation& viz)
//{
//	viz.DrawSprite(spritena)
//}

void Entity::Movement()
{
	InputHandling();
	switch (direction)
	{
	case EDirection::ELeft:
		position.widthX--;
		break;
	case EDirection::ERight:
		position.widthX++;
		break;
	case EDirection::EUp:
		position.heightY--;
		break;
	case EDirection::EDown:
		position.heightY++;
		break;
	case EDirection::EStill:
		break;
	default:
		break;
	}
}