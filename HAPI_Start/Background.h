#pragma once
#include "Entity.h"

class Background : public Entity
{
private:
	vector2<int> extraBgPos = {0,0};
	vector2<int> extraBgOldPos;

public:
	Background(const std::string& name);
	void Update(const float s) override final;
	void InputHandling() override final;

	void SetExtraBgPos(const vector2<int>& argPosition) { extraBgOldPos = extraBgPos; extraBgPos = argPosition; }
};

