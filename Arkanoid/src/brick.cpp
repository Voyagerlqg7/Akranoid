#include<iostream>
#include"../Include/brick.h"

using namespace std;

Brick::Brick(int x, int y) {
	//image.load();
	destroyed = false;
	brick_rectangle = image.rect();
	brick_rectangle.translate(x, y);
}

Brick::~Brick() {
	cout << "Brick deleted" << endl;
}

QRect Brick::get_Rect() {
	return brick_rectangle;
}

void Brick::set_Rect(QRect rct) {
	brick_rectangle = rct;
}

QImage& Brick::getImage() {
	return image;
}

bool Brick::is_Destroyed() {
	return destroyed; // если вернёт true то блок разрушен, и не будет отображаться
}

void Brick::set_Destroyed(bool destr) {
	destroyed = destr;
}