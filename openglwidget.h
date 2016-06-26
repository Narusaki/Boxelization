#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QtOpenGL/QGLWidget>
#include <QtGui/QMouseEvent>
#include "trackball.h"
#include "SimpleModel.h"
#include "SceneGraph.h"

class OpenGLWidget : public QGLWidget
{
	Q_OBJECT

public:
	OpenGLWidget(QWidget *parent = 0);
	~OpenGLWidget();

public slots:
	void timeUp();

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

public:
	TrackBall *trackball;
	SimpleSceneGraph *sceneGraph;

	double xRotate = 0.0;
};
#endif