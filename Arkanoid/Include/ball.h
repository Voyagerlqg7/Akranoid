#pragma once

#include <QImage>
#include <QRect>

class Ball {
public:
	Ball();
	~Ball();

	void resetState();
	void autoMove();

	void setXDir(int);
	void setYDir(int);

	int getXDir();
	int getYDir();

	QRect getRect();
	QImage& getImage();

private:


};