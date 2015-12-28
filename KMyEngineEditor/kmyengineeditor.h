#ifndef KMYENGINEEDITOR_H
#define KMYENGINEEDITOR_H

#include <QtWidgets/QMainWindow>
#include "ui_kmyengineeditor.h"
#include "KD3DWidget.h"
#include "KLightingTest.h"
//#include "../KMyEngine/TerrainEngineInterfaces.h"


class KMyEngineEditor : public QMainWindow
{
	Q_OBJECT

public:
	KMyEngineEditor(QWidget *parent = 0);
	~KMyEngineEditor();

	bool Init();
	void Uninit();

	void InitSlots();	

	public slots:
		void CreateTerrain();
		void SetLightDirX(int position);
		void SetLightDirY(int position);
		void SetLightDirZ(int position);
		void SetLightDirW(int position);

		
		void OnRadioClickRenderOption();

private:
	Ui::KMyEngineEditorClass ui;
	Kd3dWidget* m_pd3dWidget;

	//KLightingTest* m_lightTest;

	ITestApp	*m_piTestApp;

	void InitRenderOption();
};

#endif // KMYENGINEEDITOR_H
