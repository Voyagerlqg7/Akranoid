#include "QtWidgetsApplication1.h"
#include <QtWidgets/QApplication>
#include "Breakout.h"

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);

	Breakout window;

	window.setWindowTitle("Window");
	window.setWindowIcon(QIcon("Finch.jpg"));
	window.show();

	return a.exec();
}