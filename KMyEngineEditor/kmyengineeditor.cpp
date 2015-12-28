#include "kmyengineeditor.h"
#include <QMessageBox>

KMyEngineEditor::KMyEngineEditor(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	Init();
}

KMyEngineEditor::~KMyEngineEditor()
{
	Uninit();
}

bool KMyEngineEditor::Init()
{
	m_pd3dWidget = new Kd3dWidget;
	ui.EngineGridLayout->addWidget(m_pd3dWidget);
	m_pd3dWidget->setFocusPolicy(Qt::StrongFocus);

	/*m_lightTest = new KLightingTest;
	m_lightTest->Init(m_piTestApp,ui);*/

	InitSlots();
	InitRenderOption();

	m_piTestApp = fnCreateITerrainInterface();
	m_piTestApp->InitD3D(m_pd3dWidget->width(),m_pd3dWidget->height(), (HWND)m_pd3dWidget->winId(), GetModuleHandle(NULL));	
	m_pd3dWidget->Init(m_piTestApp);

	m_pd3dWidget->windowHandle();

	return true;
}

void KMyEngineEditor::InitSlots()
{	
	connect(ui.BTN_CreateTerrain, SIGNAL(clicked()), this, SLOT(CreateTerrain()));

	connect(ui.Slider_LightDirX, SIGNAL(valueChanged(int)), this, SLOT(SetLightDirX(int)));  
	connect(ui.Slider_LightDirY, SIGNAL(valueChanged(int)), this, SLOT(SetLightDirY(int)));  
	connect(ui.Slider_LightDirZ, SIGNAL(valueChanged(int)), this, SLOT(SetLightDirZ(int))); 
	connect(ui.Slider_LightDirW, SIGNAL(valueChanged(int)), this, SLOT(SetLightDirW(int))); 

	connect(ui.rbtn_ro_differse,SIGNAL(clicked()),this,SLOT(OnRadioClickRenderOption()));
	connect(ui.rbtn_ro_normal,SIGNAL(clicked()),this,SLOT(OnRadioClickRenderOption()));
	connect(ui.rbtn_ro_specular,SIGNAL(clicked()),this,SLOT(OnRadioClickRenderOption()));
	connect(ui.rbtn_ro_depth,SIGNAL(clicked()),this,SLOT(OnRadioClickRenderOption()));
	connect(ui.cbox_light,SIGNAL(clicked()),this,SLOT(OnRadioClickRenderOption()));
	connect(ui.cbox_edgeDetectedAll,SIGNAL(clicked()),this,SLOT(OnRadioClickRenderOption()));
	connect(ui.cbox_bloom,SIGNAL(clicked()),this,SLOT(OnRadioClickRenderOption()));



	//connect(ui.Slider_LightDirX,SIGNAL(sliderMoved()),this,SLOT(SetLightDir(int position)));

}

void KMyEngineEditor::Uninit()
{
	fnReleaseITerrainInterface(m_piTestApp);
}

void KMyEngineEditor::CreateTerrain()
{
	int level = -1;

	if (ui.RBTN_1024->isChecked())
	{
		level = 10;
	}
	if (ui.RBTN_2048->isChecked())
	{
		level = 11;
	}
	if (ui.RBTN_512->isChecked())
	{
		level = 9;
	}
	if (ui.RBTN_64->isChecked())
	{
		level = 6;
	}

	if (level ==-1)
	{
		QMessageBox::information(this,"出问题啦","地形分辨率没有选择");
		return;
	}

	bool isQstringIntOK = false;
	int cellSpacing = ui.TEXT_CellSpacing->toPlainText().toInt(&isQstringIntOK);
	if (!isQstringIntOK || cellSpacing<=0)
	{
		QMessageBox::information(this,"出问题啦","cellSpacing 输入错误");
		return;
	}

	//m_piTestApp->InitTerrain(level,cellSpacing);

	QMessageBox::information(this,"创建地形成功","成功创建分辨率等级为：" + QString(level) + "、ccellSpacing 为：" + QString(cellSpacing)+ "的地形，接下来指定其高度图吧");

}



void KMyEngineEditor::SetLightDirX(int position)
{
	//m_piTestApp

	float tValue =(float) position/100;
	QString str = QString("%1").arg(tValue);  
	ui.label_LightDirX->setText("x: " + str);

	m_piTestApp->ChangeLightDir(0,tValue);
}
void KMyEngineEditor::SetLightDirY(int position)
{
	//m_piTestApp
	float tValue =(float) position/100;
	QString str = QString("%1").arg(tValue);  
	ui.label_LightDirY->setText("y: " + str);

	m_piTestApp->ChangeLightDir(1,tValue);
}
void KMyEngineEditor::SetLightDirZ(int position)
{
	//m_piTestApp
	float tValue =(float) position/100;
	QString str = QString("%1").arg(tValue);  
	ui.label_LightDirZ->setText("z: " + str);

	m_piTestApp->ChangeLightDir(2,tValue);
}
void KMyEngineEditor::SetLightDirW(int position)
{
	//m_piTestApp
	float tValue =(float) position/100;
	QString str = QString("%1").arg(tValue);  
	ui.label_LightDirW->setText("w: " + str);

	m_piTestApp->ChangeLightDir(3,tValue);
}

void KMyEngineEditor::OnRadioClickRenderOption()
{
	if (ui.cbox_bloom->isChecked())
	{
		m_pd3dWidget->setRenderOption(6);

		return ;
	}
	if (ui.cbox_edgeDetectedAll->isChecked())
	{
		m_pd3dWidget->setRenderOption(5);
		return ;
	}
	if (ui.cbox_light->isChecked())
	{
		m_pd3dWidget->setRenderOption(4);
		return ;
	}

	int tt = ui.btnGroup_Ro_GBuffer->checkedId();
	switch(ui.btnGroup_Ro_GBuffer->checkedId())  
	{  
	case 0:  
		m_pd3dWidget->setRenderOption(0);
		break;  
	case 1:  
		m_pd3dWidget->setRenderOption(1); 
		break;  
	case 2:  
		m_pd3dWidget->setRenderOption(2);
		break;  
	default:
		m_pd3dWidget->setRenderOption(3);
		break;
	}
	return ;

}

void KMyEngineEditor::InitRenderOption()
{
	ui.btnGroup_Ro_GBuffer->setId(ui.rbtn_ro_differse,0);//topTubePositionRadio的Id设为0  
	ui.btnGroup_Ro_GBuffer->setId(ui.rbtn_ro_normal,1);  
	ui.btnGroup_Ro_GBuffer->setId(ui.rbtn_ro_specular,2);  
	ui.btnGroup_Ro_GBuffer->setId(ui.rbtn_ro_depth,3);  
}