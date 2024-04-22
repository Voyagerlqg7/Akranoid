#include <iostream>
#include "../Include/paddle.h"

using namespace std;

Paddle::Paddle() {
	DX = 0;
	//image.load("");
	rectangle = image.rect(); //ѕр€моугольник ограничивает загруженное изображение
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
	//«десь работа с перемещением пр€моугольника с избражением 
	rectangle.moveTo(x, y);
}

void Paddle::resetState() {
	rectangle.moveTo(INITIAL_X, INITIAL_Y); //установка в исходное положение 
}

QRect Paddle::getRect() {
	return rectangle;
}

QImage Paddle::getImage() {
	return image;
}