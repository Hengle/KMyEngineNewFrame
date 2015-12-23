#ifndef KMYENGINEEDITOR_H
#define KMYENGINEEDITOR_H

#include <QtWidgets/QMainWindow>
#include "ui_kmyengineeditor.h"
#include "KD3DWidget.h"
//#include "../KMyEngine/TerrainEngineInterfaces.h"


class KMyEngineEditor : public QMainWindow
{
	Q_OBJECT

public:
	KMyEngineEditor(QWidget *parent = 0);
	~KMyEngineEditor();

	bool Init();
	void Uninit();

	public slots:
		void CreateTerrain();


private:
	Ui::KMyEngineEditorClass ui;
	Kd3dWidget* m_pd3dWidget;

	ITestApp	*m_piTestApp;
};

#endif // KMYENGINEEDITOR_H
