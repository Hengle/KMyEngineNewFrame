#ifndef _K_D3D_WIDGET_H_
#define _K_D3D_WIDGET_H_

#include <QWidget>
#include <QMouseEvent>
#include "../KMyEngine/MyTestInterfaces.h"

class Kd3dWidget : public QWidget
{
	Q_OBJECT
public:
	Kd3dWidget(QWidget *parent = 0);
	~Kd3dWidget();

	bool Init(ITestApp* pApp);
	bool UnInit();

	void setRenderOption(int type);

protected:

	void paintEvent(QPaintEvent* pEvent);
	void resizeEvent(QResizeEvent* pEvent);

	QPaintEngine *paintEngine() const;

	void mouseMoveEvent(QMouseEvent* pEvent);
	void mousePressEvent(QMouseEvent* pEvent);
	void wheelEvent(QWheelEvent* pEvent);

	void keyReleaseEvent(QKeyEvent *e);
	void keyPressEvent(QKeyEvent * e);

	

private:

	bool m_isPressingW;
	bool m_isPressingS;
	bool m_isPressingA;
	bool m_isPressingD;

	int m_nCurMousePosX;
	int m_nCurMousePosY;

	int m_d3dRenderOption;

	ITestApp   *m_piTestApp;
};

#endif // _K_D3D_WIDGET_H_
