#include "KLightingTest.h"


KLightingTest::KLightingTest(void)
{
	m_piTestApp = NULL;
}


KLightingTest::~KLightingTest(void)
{
}

void KLightingTest::Init(ITestApp* p,Ui::KMyEngineEditorClass ui)
{
	m_piTestApp = p;
	m_ui = ui;

 
}

void KLightingTest::Unint()
{

}

//void KLightingTest::SetLightDirX(int position)
//{
//	//m_piTestApp
//
//	float tValue =(float) position/100;
//	QString str = QString("%1").arg(tValue);  
//	m_ui.label_LightDirX->setText("x: " + str);
//
//	m_piTestApp->ChangeLightDir(0,tValue);
//}
//void KLightingTest::SetLightDirY(int position)
//{
//	//m_piTestApp
//	float tValue =(float) position/100;
//	QString str = QString("%1").arg(tValue);  
//	m_ui.label_LightDirY->setText("y: " + str);
//
//	m_piTestApp->ChangeLightDir(1,tValue);
//}
//void KLightingTest::SetLightDirZ(int position)
//{
//	//m_piTestApp
//	float tValue =(float) position/100;
//	QString str = QString("%1").arg(tValue);  
//	m_ui.label_LightDirZ->setText("z: " + str);
//
//	m_piTestApp->ChangeLightDir(2,tValue);
//}
