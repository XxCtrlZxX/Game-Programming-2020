#pragma once

#include "Scene.h"
#include "Sprite.h"
#include "Animation.h"
#include "MainScene.h"
#include <list>
#include <math.h>

// 오브젝트 헤더
#include "Player.h"
#include "Wall.h"

class MyGameScene : public Scene
{
private:
	Player* player;
	Sprite* arrow;
	std::list<Wall*> wallList;

	float arrowLen;
	bool isLBtnDown, isLBtnUp;
	int jumpCount;

	D3DXVECTOR2 firstMousePos, currentMousePos, cameraPos;
	D3DXVECTOR2 arrowVector, cameraVector;

public:
	MyGameScene();
	~MyGameScene();

	void Render();
	void Update(float dTime);

	void CollisionCheck();
	void MouseManage();
	
	void CameraDiff();
	void CameraMove(D3DXVECTOR2 vec);
	void CameraMove(float dx, float dy);

	float VecDistance(D3DXVECTOR2 vec);
	float VecAngle(D3DXVECTOR2 vec);
	float Lerp(float p1, float p2, float d1);
};

