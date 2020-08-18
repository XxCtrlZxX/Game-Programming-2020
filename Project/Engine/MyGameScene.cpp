#include "stdafx.h"
#include "MyGameScene.h"

MyGameScene::MyGameScene() {
	arrowLen = 0;
	jumpCount = 0;
	isLBtnDown = false;
	isLBtnUp = false;

	//-------------------------------------------//
	player = new Player();
	player->setPos(SCREEN_WIDTH / 2 - 50, 100);
	player->setScale(0.6, 0.6);
	AddObject(player);

	//-------------------------------------------//
	arrow = new Sprite("Resources/Image/arrow.png");
	arrow->setRotationCenter(0, arrow->getHeight() / 2);
	AddObject(arrow);

	//-------------------------------------------//
	Wall* wall = new Wall("Resources/Image/ground.png");
	wall->setPos(200, SCREEN_HEIGHT - 300);
	//wall->setScale(SCREEN_WIDTH / 768, 1);
	wallList.push_back(wall);
	AddObject(wall);

	Wall* wall2 = new Wall("Resources/Image/ground.png");
	wall2->setPos(0, 0);
	wall2->setScale(1, 0.5);
	wallList.push_back(wall2);
	AddObject(wall2);
}

MyGameScene::~MyGameScene() {

}

void MyGameScene::Render() {
	for (auto& wall : wallList)
		wall->Render();

	player->Render();

	if (isLBtnDown)
		arrow->Render();
}

void MyGameScene::Update(float dTime) {
	Scene::Update(dTime);

	CollisionCheck();

	if (inputManager->GetKeyState(VK_SPACE) == KEY_DOWN) {
		player->isPlayerAnim = player->isPlayerAnim ? false : true;
	}

	if (jumpCount < 2) {
		MouseManage();
	}
	
}

void MyGameScene::CollisionCheck() {
	for (auto iter = wallList.begin(); iter != wallList.end(); iter++) {
		if (player->IsCollisionRect((*iter)) && !player->isGround) {
			debug("collide");
			player->isGround = true;
			jumpCount = 0;
		}
	}
}

void MyGameScene::MouseManage() {
	// mouse click
	if (inputManager->GetKeyState(VK_LBUTTON) == KEY_DOWN) {
		firstMousePos = inputManager->GetMousePos();
		isLBtnDown = true;
		globalTime = 0.35;
	}
	if (inputManager->GetKeyState(VK_LBUTTON) == KEY_UP) {
		isLBtnDown = false;
		isLBtnUp = true;
		globalTime = 1;
	}

	if (isLBtnDown) {
		//std::cout << "ÁÂÅ¬¸¯ Áß" << std::endl;

		currentMousPos = inputManager->GetMousePos();

		arrowVector = currentMousPos - firstMousePos;

		if (VecDistance(arrowVector) < 200)
			arrowLen = VecDistance(arrowVector);
		else
			arrowLen = 200;

		arrow->setScale(arrowLen / 200, 1);
		arrow->setRotation(VecAngle(arrowVector) + PI / 2);
		arrow->setPos(player->getPosCenter());

		//std::cout << "x: " << arrowVector.x << ", y: " << arrowVector.y << std::endl;
	}
	else if (isLBtnUp) {
		//std::cout << "ÁÂÅ¬¸¯ ¶À" << std::endl;
		isLBtnUp = false;

		player->isGround = false;
		player->PlayerJump(arrowVector / VecDistance(arrowVector) * 3, arrowLen);
		jumpCount++;
	}
}

float MyGameScene::VecDistance(D3DXVECTOR2 vec) {
	return sqrt(vec.x * vec.x + vec.y * vec.y);;
}

float MyGameScene::VecAngle(D3DXVECTOR2 vec) {
	return -atan2(vec.x, vec.y);
}
