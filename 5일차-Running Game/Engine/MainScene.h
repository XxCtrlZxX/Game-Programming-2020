#pragma once

#include "Scene.h"
#include "Sprite.h"
#include "GameScene.h"

class MainScene : public Scene
{
public:
	MainScene();
	~MainScene();

	Sprite* background;
	Sprite* title;
	Sprite* startButton;
	Sprite* exitButton;
	// Sprite* explainButton;

	void Render();
	void Update(float dTime);
};

