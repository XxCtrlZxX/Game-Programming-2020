#pragma once
#include "Object.h"
#include "Animation.h"

class Player : public Object
{
private :
	Animation* playerAnimation;
	float gravity;
	bool doubleJump, isJump;

	D3DXVECTOR2 center;

public :
	bool isPlayerAnim;

	Player();
	~Player();

	void Render();
	void Update(float dTime);

	D3DXVECTOR2 getPosCenter();
};