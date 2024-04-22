#pragma once

#include<QImage>
#include<QRect>

class Brick {
public:
	Brick(int, int);
	~Brick();

	bool is_Destroyed();
	void set_Destroyed(bool);
	QRect get_Rect();
	void set_Rect(QRect);
	QImage& getImage();

private:
	QImage image;
	QRect brick_rectangle;
	bool destroyed;
};