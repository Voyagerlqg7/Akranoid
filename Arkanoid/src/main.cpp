#include <QtWidgets/QApplication>
#include "Arkanoid.h"

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);

	Arkanoid window;
	window.setWindowTitle("Arkanoid");
	window.setWindowIcon(QIcon("textures/Paddle_1.png"));
	window.show();
	
	return a.exec();
}