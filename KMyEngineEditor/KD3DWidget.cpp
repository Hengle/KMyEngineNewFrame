#include "Kd3dWidget.h"
#include <QTimer>

Kd3dWidget::Kd3dWidget(QWidget *parent) : QWidget(parent)
{
	setAttribute(Qt::WA_PaintOnScreen, true);
	//setAttribute(Qt::WA_NativeWindow, true);

	QTimer *pqTimer = new QTimer(this);
	connect(pqTimer, SIGNAL(timeout()), this, SLOT(update()));
	pqTimer->start(20);

}

Kd3dWidget::~Kd3dWidget()
{
	UnInit();
}

bool Kd3dWidget::Init(ITestApp* pApp)
{
	m_nCurMousePosX = -1;
	m_nCurMousePosY = -1;

	m_piTestApp = pApp;
	setMouseTracking(true);

	m_isPressingW = false;
	m_isPressingS = false;
	m_isPressingA = false;
	m_isPressingD = false;

	return true;
}

bool Kd3dWidget::UnInit()
{

	return true;
}

void Kd3dWidget::paintEvent(QPaintEvent* pEvent)
{	
	if (m_isPressingW)
	{
		m_piTestApp->KeyInput('w');
	}
	if (m_isPressingS)
	{
		m_piTestApp->KeyInput('s');
	}
	if (m_isPressingA)
	{
		m_piTestApp->KeyInput('a');
	}
	if (m_isPressingD)
	{
		m_piTestApp->KeyInput('d');
	}

	m_piTestApp->DrawScene();


}
void Kd3dWidget::resizeEvent(QResizeEvent* pEvent)
{
	m_piTestApp->OnResize(width(), height());
}

QPaintEngine* Kd3dWidget::paintEngine() const
{
	return NULL;
}

void Kd3dWidget::mouseMoveEvent(QMouseEvent* pEvent)
{
	if(pEvent->buttons() & Qt::RightButton)
	{
		m_piTestApp->OnMouseMove(1,pEvent->x(),pEvent->y());
	}
	if(pEvent->buttons() & Qt::LeftButton)
	{
		m_piTestApp->OnMouseMove(0,pEvent->x(),pEvent->y());
	}	

}
void Kd3dWidget::mousePressEvent(QMouseEvent* pEvent)
{
	m_piTestApp->OnMouseDown(0,pEvent->x(),pEvent->y());
}
void Kd3dWidget ::wheelEvent(QWheelEvent* pEvent)
{

}

void Kd3dWidget:: keyPressEvent(QKeyEvent * e)
{
	int keyValue = e->key();
	if ( e->key() == Qt::Key_W  && !e->isAutoRepeat())
	{
		m_isPressingW = true;
	}
	if (e->key() ==  Qt::Key_S  && !e->isAutoRepeat())
	{
		m_isPressingS = true;
	}
	if (e->key() ==  Qt::Key_A && !e->isAutoRepeat())
	{
		m_isPressingA = true;
	}
	if (e->key() ==  Qt::Key_D && !e->isAutoRepeat())
	{
		m_isPressingD = true;
	}
	QWidget::keyPressEvent(e);

	e->ignore();
}

void Kd3dWidget::keyReleaseEvent(QKeyEvent *e)
{
	int keyValue = e->key();
	if (e->key() ==  Qt::Key_W && !e->isAutoRepeat())
	{
		m_isPressingW = false;
	}
	if (e->key() ==  Qt::Key_S && !e->isAutoRepeat())
	{
		m_isPressingS = false;
	}
	if (e->key() ==  Qt::Key_A && !e->isAutoRepeat())
	{
		m_isPressingA = false;
	}
	if (e->key() ==  Qt::Key_D && !e->isAutoRepeat())
	{
		m_isPressingD = false;
	}
	QWidget::keyPressEvent(e);

	e->ignore();
}
