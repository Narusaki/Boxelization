#include "openglwidget.h"
#include <gl\GL.h>

OpenGLWidget::OpenGLWidget(QWidget *parent) : QGLWidget(parent)
{

}

OpenGLWidget::~OpenGLWidget()
{

}


void OpenGLWidget::initializeGL()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClearDepth(1.0);
	glEnable(GL_DEPTH_TEST);
}

void OpenGLWidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLWidget::resizeGL(int width, int height)
{

}

void OpenGLWidget::mouseMoveEvent(QMouseEvent* event)
{

}

void OpenGLWidget::mousePressEvent(QMouseEvent* event)
{

}

void OpenGLWidget::mouseDoubleClickEvent(QMouseEvent* event)
{

}

void OpenGLWidget::mouseReleaseEvent(QMouseEvent* event)
{

}

void OpenGLWidget::keyPressEvent(QKeyEvent *event)
{

}

void OpenGLWidget::keyReleaseEvent(QKeyEvent *event)
{

}

void OpenGLWidget::dragEnterEvent(QDragEnterEvent *event)
{

}

void OpenGLWidget::dragMoveEvent(QDragMoveEvent *event)
{

}

void OpenGLWidget::dropEvent(QDropEvent *event)
{

}