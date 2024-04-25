#include <QtWidgets/QApplication>
#include "Arkanoid.h"

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);

	Arkanoid window;

	window.setWindowTitle("Window");
	window.setWindowIcon(QIcon("src/textures/paddle.jpg"));
	window.show();

	return a.exec();
}