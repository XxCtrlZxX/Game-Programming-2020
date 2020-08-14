#include "stdafx.h"
#include "Player.h"

Player::Player() {
	isJump = doubleJump = false;
	gravity = 9.8;

	playerAnimation = new Animation(5);
	playerAnimation->AddFrame("Resources/Image/player-stop.png");
	playerAnimation->AddFrame("Resources/Image/player-run.png");
	AddChild(playerAnimation);

	rect = playerAnimation->getRect();
}

Player::~Player() {

}

void Player::Render() {
	Object::Render();
	playerAnimation->Render();
}

void Player::Update(float dTime) {
	setPos(getPosX(), getPosY() + gravity * dTime);	// 중력 적용

	if (isJump) {	// 점프 메커니즘
		setPos(getPosX(), getPosY() - 400 * dTime);
		
		if (inputManager->GetKeyState(VK_SPACE) == KEY_DOWN) {
			doubleJump = true;
		}
		if (doubleJump) {
			setPos(getPosX(), getPosY() - 150 * dTime);
		}
	}
	if (getPosY() > 345) {
		setPos(getPosX(), 345);
		doubleJump = false;
		isJump = false;
	}
	else {
		gravity += 9.8f;
	}
	if (inputManager->GetKeyState(VK_SPACE) == KEY_DOWN) {
		if (getPosY() >= 345) {
			isJump = true;
			gravity = 0;
		}
	}

	playerAnimation->Update(dTime);
}