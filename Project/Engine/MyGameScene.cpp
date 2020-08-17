#include "stdafx.h"
#include "MyGameScene.h"

MyGameScene::MyGameScene() {
	gravity = 0;
	isLBtnDown = false;
	isLBtnUp = false;

	player = new Player();
	player->setPos(100, 100);
	player->setScale(0.8, 0.8);
	AddObject(player);


	arrow = new Sprite("Resources/Image/arrow.png");
	arrow->setPos(200, 200);
	arrow->setRotationCenter(0, arrow->getHeight() / 2);
	AddObject(arrow);
}

MyGameScene::~MyGameScene() {

}

void MyGameScene::Render() {
	player->Render();
	if (isLBtnDown)
		arrow->Render();
}

void MyGameScene::Update(float dTime) {
	Scene::Update(dTime);
	if (inputManager->GetKeyState(VK_SPACE) == KEY_DOWN) {
		player->isPlayerAnim = player->isPlayerAnim ? false : true;
	}

	if (inputManager->GetKeyState(VK_LBUTTON) == KEY_DOWN) {
		firstMousePos = inputManager->GetMousePos();
		isLBtnDown = true;
	}
	if (inputManager->GetKeyState(VK_LBUTTON) == KEY_UP) {
		isLBtnDown = false;
		isLBtnUp = true;
	}

	if (isLBtnDown) {
		//std::cout << "ÁÂÅ¬¸¯ Áß" << std::endl;
		currentMousPos = inputManager->GetMousePos();

		// TODO: arrowVector
		arrowVector = currentMousPos - firstMousePos;

		arrow->setPos(player->getPosCenter());
		arrow->setScale(VecDistance(arrowVector) / 200, 1);
		arrow->setRotation(VecAngle(arrowVector));
	}
	else if (isLBtnUp) {
		//std::cout << "ÁÂÅ¬¸¯ ¶À" << std::endl;
		isLBtnUp = false;
	}
}

float MyGameScene::VecDistance(D3DXVECTOR2 vec) {
	return sqrt(vec.x * vec.x + vec.y * vec.y);;
}

float MyGameScene::VecAngle(D3DXVECTOR2 vec) {
	return -atan2(vec.x, vec.y) + PI / 2;
}
