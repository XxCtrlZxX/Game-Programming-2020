#pragma once

#include "Object.h"
#include "Animation.h"

class Player : public Object
{
private:
	float gravity;
	bool doubleJump, isJump;

	Animation* playerAnimation;

public:
	Player();
	~Player();

	void Render();
	void Update(float dTime);
};

