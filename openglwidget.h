#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QtOpenGL/QGLWidget>
#include <QtGui/QMouseEvent>
#include "trackball.h"
#include "SimpleModel.h"

class OpenGLWidget : public QGLWidget
{
	Q_OBJECT

public:
	OpenGLWidget(QWidget *parent = 0);
	~OpenGLWidget();

protected:
	void initializeGL();
	void paintGL();
	void resizeGL(int width, int height);
	void mouseMoveEvent(QMouseEvent* event);
	void mousePressEvent(QMouseEvent* event);
	void mouseDoubleClickEvent(QMouseEvent* event);
	void mouseReleaseEvent(QMouseEvent* event);
	void keyPressEvent(QKeyEvent *event);
	void keyReleaseEvent(QKeyEvent *event);
	void dragEnterEvent(QDragEnterEvent *event);
	void dragMoveEvent(QDragMoveEvent *event);
	void dropEvent(QDropEvent *event);

private:
	TrackBall *trackball;
	// test model
	SimpleModel *modelTest;
};
#endif