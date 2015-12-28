#pragma once
#include "KD3DWidget.h"
#include "ui_kmyengineeditor.h"

class KLightingTest : public QObject
{
public:
	KLightingTest(void);
	~KLightingTest(void);

	void Init(ITestApp* p,Ui::KMyEngineEditorClass ui);
	void Unint();

	ITestApp *m_piTestApp;
	Ui::KMyEngineEditorClass m_ui;

	public slots:
		//void SetLightDirX(int position);
		//void SetLightDirY(int position);
		//void SetLightDirZ(int position);
		//void SetLightDirW(int position);


};

