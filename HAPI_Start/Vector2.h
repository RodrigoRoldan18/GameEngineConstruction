#pragma once
#include <cmath>

template<class T>
class vector2
{
public:
	T widthX;
	T heightY;

	vector2() = default;
	vector2(T newX, T newY) : widthX(newX), heightY(newY) {}

	//+ operator, returns the result of adding the rhs to this
	vector2<T> operator + (const vector2<T>& rhs) const
	{
		return vector2<T>(widthX + rhs.widthX, heightY + rhs.heightY);
	}
	//- operator, returns the result of subtracting the rhs to this
	vector2<T> operator - (const vector2<T>& rhs) const
	{
		return vector2<T>(widthX - rhs.widthX, heightY - rhs.heightY);
	}
	//* operator, returns the result of multiplying the rhs to this
	vector2<T> operator * (const float rhs) const
	{
		return vector2<T>(widthX * rhs, heightY * rhs);
	}
	//
	vector2<T> operator / (const float rhs) const
	{
		return vector2<T>(widthX / rhs, heightY / rhs);
	}
};