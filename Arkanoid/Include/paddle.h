#pragma once

#include <QImage>
#include <QRect>

class Paddle {
public:
	Paddle();
	~Paddle();

	void resetState();
	void move();
	void set_DX(int); //��� �������� X ��� paddle
	QRect getRect();
	QImage getImage();

private:
	QImage image; // �� ���� ��������, �� � Qt ������ ������� ���
	QRect rectangle; //������ �����
	int DX; //���������� ���������

	//��������� ���������� ��������� paddle
	static const int INITIAL_X = 200;
	static const int INITIAL_Y = 360;
};