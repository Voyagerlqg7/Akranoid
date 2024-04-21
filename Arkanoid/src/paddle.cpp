#include <iostream>
#include "../Include/paddle.h"

using namespace std;

Paddle::Paddle() {
	DX = 0;
	//image.load("");
	rectangle = image.rect();
	resetState();
}

Paddle::~Paddle() {
	cout << ("Paddle deleted") << endl;
}

void Paddle::set_DX(int x) {
	DX = x;
}

void Paddle::move() {
	int x = rectangle.x() + DX;
	int y = rectangle.top();

	rectangle.moveTo(x, y);
}

void Paddle::resetState() {
	rectangle.moveTo(INITIAL_X, INITIAL_Y);
}

QRect Paddle::getRect() {
	return rectangle;
}

QImage Paddle::getImage() {
	return image;
}