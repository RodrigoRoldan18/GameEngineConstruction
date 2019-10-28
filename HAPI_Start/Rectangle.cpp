#include "Rectangle.h"
#include <algorithm>

Rectangle::Rectangle()
{
}

Rectangle::~Rectangle()
{
}

bool Rectangle::CompletelyOutside(const Rectangle& other)
{	
	if (left > other.right) { return true; }
	if (bottom < other.top) { return true; }
	if (right < other.left) { return true; }
	if (top > other.bottom) { return true; }	
	return false;
}

bool Rectangle::CompletelyInside(const Rectangle& other)
{
	if (left < other.left) { return false; }
	if (top < other.top) { return false; }
	if (right > other.right) { return false; }
	if (bottom > other.bottom) { return false; }
	return true;
}

void Rectangle::ClippingTo(const Rectangle& other)
{
	left = std::max(left, other.left);
	top = std::max(top, other.top);
	right = std::max(right, other.right);
	bottom = std::max(bottom, other.bottom);
}

void Rectangle::Translate(const int& posX, const int& posY)
{
	left += posX;
	right += posX;
	top += posY;
	bottom += posY;
}
