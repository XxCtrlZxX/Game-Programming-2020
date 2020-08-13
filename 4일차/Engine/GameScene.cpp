#include "stdafx.h"
#include "GameScene.h"

GameScene::GameScene() {
	gravity = 0;
	doubleJump = isJump = false;

	//-----------------------------------------------------------------

	backgroundList.push_back(new Sprite("Resources/Image/Background.png"));
	
	Sprite* tmpBackground = new Sprite("Resources/Image/Background.png");
	tmpBackground->setPos(SCREEN_WIDTH, 0);
	backgroundList.push_back(tmpBackground);

	//-----------------------------------------------------------------

	Sprite* tmpBridge1 = new Sprite("Resources/Image/LoopMap.png");
	tmpBridge1->setPos(0, 500);
	bridgeList.push_back(tmpBridge1);

	Sprite* tmpBridge2 = new Sprite("Resources/Image/LoopMap.png");
	tmpBridge2->setPos(SCREEN_WIDTH, 500);
	bridgeList.push_back(tmpBridge2);

	//-----------------------------------------------------------------

	player = new Animation(2);
	player->AddFrame("Resources/Image/player-stop.png");
	player->AddFrame("Resources/Image/player-run.png");
	player->setPos(50, 100);
}

GameScene::~GameScene() {

}

void GameScene::Render() {
	for (auto& background : backgroundList) {
		background->Render();
	}
	for (auto& bridge : bridgeList) {
		bridge->Render();
	}
	player->Render();
}

void GameScene::Update(float dTime) {
	Scene::Update(dTime);
	gravity += 9.8f;

	player->setPos(player->getPosX(), player->getPosY() + gravity * dTime);	// 중력 적용

	if (isJump) {	// 점프 메커니즘

		player->setPos(player->getPosX(), player->getPosY() - 300 * dTime);

		if (inputManager->GetKeyState(VK_SPACE) == KEY_DOWN) {
			doubleJump = true;
		}
		if (doubleJump) {
			player->setPos(player->getPosX(), player->getPosY() - 250 * dTime);
		}
	}
	if (player->getPosY() > 345) {
		player->setPos(player->getPosX(), 345);
		doubleJump = false;
		isJump = false;
	}
	if (inputManager->GetKeyState(VK_SPACE) == KEY_DOWN) {
		if (player->getPosY() >= 345) {
			isJump = true;
			gravity = 0;
		}
	}


	player->Update(dTime);

	//-----------------------------------------------------------------

	int bgDiff = 500 * dTime;

	//--- Background ---
	for (auto iter = backgroundList.begin(); iter != backgroundList.end(); iter++) {
		
		(*iter)->setPos((*iter)->getPosX() - bgDiff, (*iter)->getPosY());

		if ((*iter)->getPosX() < -SCREEN_WIDTH) {
			
			SAFE_DELETE(*iter);
			iter = backgroundList.erase(iter);

			Sprite* tmpBackground = new Sprite("Resources/Image/Background.png");
			tmpBackground->setPos((*iter)->getWidth() - 10, 0);
			backgroundList.push_back(tmpBackground);
			
			if (iter == backgroundList.end()) {
				break;
			}
		}
	}

	//--- Bridge ---
	for (auto iter = bridgeList.begin(); iter != bridgeList.end(); iter++) {

		(*iter)->setPos((*iter)->getPosX() - bgDiff, (*iter)->getPosY());

		if ((*iter)->getPosX() < -SCREEN_WIDTH) {

			SAFE_DELETE(*iter);
			iter = bridgeList.erase(iter);

			Sprite* tmpBridge = new Sprite("Resources/Image/LoopMap.png");
			tmpBridge->setPos((*iter)->getWidth() - 10, 500);
			bridgeList.push_back(tmpBridge);

			if (iter == bridgeList.end()) {
				break;
			}
		}
	}
}