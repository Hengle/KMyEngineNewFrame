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

	connect(ui.BTN_CreateTerrain, SIGNAL(clicked()), this, SLOT(CreateTerrain()));

	m_piTestApp = fnCreateITerrainInterface();
	m_piTestApp->InitD3D(m_pd3dWidget->width(),m_pd3dWidget->height(), (HWND)m_pd3dWidget->winId(), GetModuleHandle(NULL));	
	m_pd3dWidget->Init(m_piTestApp);

	m_pd3dWidget->windowHandle();

	return true;
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