#include "stdafx.h"
#include "Background.h"

Background::Background() {
	background = new Sprite("Resources/Image/Background.png");
	AddChild(background);
}

Background::~Background() {

}

void Background::Render() {
	Object::Render();
	background->Render();
}

void Background::Update(float dTime) {
	Object::Update(dTime);

	int bgDiff = 400 * dTime;
	setPos(getPosX() - bgDiff, getPosY());
}