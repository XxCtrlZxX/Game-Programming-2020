#include "stdafx.h"
#include "GameScene.h"

GameScene::GameScene() {
	score = 0;
	time = 0;
	backgroundInstantiate = false;

	//-----------------------------------------------------------------
	
	Background* background = new Background();
	background->setPos(0, 0);
	backgroundList.push_back(background);
	AddObject(background);

	//-----------------------------------------------------------------

	Sprite* tmpBridge1 = new Sprite("Resources/Image/LoopMap.png");
	tmpBridge1->setPos(0, 500);
	bridgeList.push_back(tmpBridge1);

	Sprite* tmpBridge2 = new Sprite("Resources/Image/LoopMap.png");
	tmpBridge2->setPos(SCREEN_WIDTH, 500);
	bridgeList.push_back(tmpBridge2);

	//-----------------------------------------------------------------

	Sprite* tmpCoin = new Sprite("Resources/Image/coin-yellow.png");
	tmpCoin->setPos(SCREEN_WIDTH + 70, 450);
	coinList.push_back(tmpCoin);

	Sprite* tmpObstacle = new Sprite("Resources/Image/Drop.png");
	tmpObstacle->setPos(SCREEN_WIDTH, 460);
	obstacleList.push_back(tmpObstacle);

	//-----------------------------------------------------------------

	for (int i = 0; i < 4; i++) {
		numArray[i].setPos(10 + i * 40, 10);
	}

	player = new Player();
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
	for (auto& obstacle : obstacleList) {
		obstacle->Render();
	}
	for (auto& coin : coinList) {
		coin->Render();
	}
	player->Render();
	for (int i = 0; i < 4; i++) {
		numArray[i].Render();
	}
}

void GameScene::Update(float dTime) {
	Scene::Update(dTime);

	// 内牢 积己
	if (time > 0.25) {
		time = 0;
		Sprite* tmpCoin = new Sprite("Resources/Image/coin-yellow.png");
		tmpCoin->setPos(SCREEN_WIDTH + 200, 450);
		coinList.push_back(tmpCoin);
	}
	else
		time += dTime;

	numArray[0].setNum(score / 1000);
	numArray[1].setNum(score / 100 % 10);
	numArray[2].setNum(score / 10 % 10);
	numArray[3].setNum(score % 10);

	player->Update(dTime);

	//-----------------------------------------------------------------

	//--- Background ---
	for (auto iter = backgroundList.begin(); iter != backgroundList.end(); iter++) {

		if ((*iter)->getPosX() < -SCREEN_WIDTH) {
			RemoveObject((*iter));
			SAFE_DELETE(*iter);
			backgroundInstantiate = false;
			iter = backgroundList.erase(iter);
			
			if (iter == backgroundList.end()) {
				break;
			}
		}
	}
	if (!backgroundInstantiate) {
		Background* background = new Background();
		background->setPos(SCREEN_WIDTH - 20, 0);
		backgroundList.push_back(background);
		AddObject(background);

		backgroundInstantiate = true;
	}

	//--- Bridge ---
	int bridgeDiff = 500 * dTime;
	
	for (auto iter = bridgeList.begin(); iter != bridgeList.end(); iter++) {

		(*iter)->setPos((*iter)->getPosX() - bridgeDiff, (*iter)->getPosY());

		if ((*iter)->getPosX() < -SCREEN_WIDTH) {

			SAFE_DELETE(*iter);
			iter = bridgeList.erase(iter);

			Sprite* tmpBridge = new Sprite("Resources/Image/LoopMap.png");
			tmpBridge->setPos(SCREEN_WIDTH, (*iter)->getPosY());
			bridgeList.push_back(tmpBridge);

			if (iter == bridgeList.end()) {
				break;
			}
		}
	}

	//--- Obstacle ---
	for (auto iter = obstacleList.begin(); iter != obstacleList.end(); iter++) {

		(*iter)->setPos((*iter)->getPosX() - bridgeDiff, (*iter)->getPosY());

		// collide
		if (player->IsCollisionRect((*iter))) {
			sceneManager->ChangeScene(new MainScene());
			return;
		}

		if ((*iter)->getPosX() < -SCREEN_WIDTH) {

			SAFE_DELETE(*iter);
			iter = obstacleList.erase(iter);

			Sprite* tmpObstacle = new Sprite("Resources/Image/Drop.png");
			tmpObstacle->setPos(SCREEN_WIDTH, 450);
			obstacleList.push_back(tmpObstacle);

			if (iter == obstacleList.end()) {
				break;
			}
		}
	}

	//--- Coin ---
	for (auto iter = coinList.begin(); iter != coinList.end(); iter++) {

		(*iter)->setPos((*iter)->getPosX() - bridgeDiff, (*iter)->getPosY());

		if ((*iter)->getPosX() < -SCREEN_WIDTH) {

			SAFE_DELETE(*iter);
			iter = coinList.erase(iter);

			if (iter == coinList.end()) {
				break;
			}
		}
	}
	// 货肺 父电 coinList for loop
	for (auto iter = coinList.begin(); iter != coinList.end(); iter++) {
		// collide
		if (player->IsCollisionRect((*iter))) {
			score++;

			SAFE_DELETE(*iter);
			iter = coinList.erase(iter);

			if (iter == coinList.end()) {
				break;
			}
		}
	}
}