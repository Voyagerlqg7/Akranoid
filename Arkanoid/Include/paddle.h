#pragma once

#include <QImage>
#include <QRect>

class Paddle {
public:
	Paddle();
	~Paddle();

	void resetState();
	void move();
	void set_DX(int); //Ось движения X для paddle
	QRect getRect();
	QImage getImage();

private:
	QImage image; // По сути текстура, но в Qt такого понятия нет
	QRect rectangle; //Объект блока
	int DX; //координата положения

	//Начальный координаты положения paddle
	static const int INITIAL_X = 200;
	static const int INITIAL_Y = 360;
};