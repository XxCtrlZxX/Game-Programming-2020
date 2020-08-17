#pragma once

#include "Scene.h"
#include "Sprite.h"
#include "Animation.h"
#include "MainScene.h"
#include <list>
#include <math.h>

// 오브젝트 헤더
#include "Player.h"

class MyGameScene : public Scene
{
private:
	Player* player;
	Sprite* arrow;

	float gravity;
	bool isLBtnDown, isLBtnUp;

	D3DXVECTOR2 firstMousePos, currentMousPos;
	D3DXVECTOR2 arrowVector;

public:
	MyGameScene();
	~MyGameScene();

	void Render();
	void Update(float dTime);

	float VecDistance(D3DXVECTOR2 vec);
	float VecAngle(D3DXVECTOR2 vec);
};

