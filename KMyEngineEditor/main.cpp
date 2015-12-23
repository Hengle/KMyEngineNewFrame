#include "kmyengineeditor.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	KMyEngineEditor w;

	HINSTANCE hInstance = GetModuleHandle(NULL);

	w.show();
	return a.exec();
}
