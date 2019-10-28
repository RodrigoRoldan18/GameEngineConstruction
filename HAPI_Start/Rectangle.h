#pragma once
class Rectangle
{
public:
	int left{ 0 }, right{ 0 }, top{ 0 }, bottom{ 0 };

	Rectangle();
	~Rectangle();

	bool CompletelyOutside(const Rectangle& other);	
	bool CompletelyInside(const Rectangle& other);
	void ClippingTo(const Rectangle& other);
	void Translate(const int& posX, const int& posY);

	int Width() const { return right - left; }
	int Height() const { return bottom - top; }

};