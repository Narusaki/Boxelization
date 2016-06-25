#include "openglwidget.h"
#include <gl\GLU.h>

OpenGLWidget::OpenGLWidget(QWidget *parent) : QGLWidget(parent)
{
	trackball = new TrackBall();
	trackball->init();

	sceneGraph = new SimpleSceneGraph();
	sceneGraph->LoadModel("H:\\Graphics\\Boxelization\\out");
}

OpenGLWidget::~OpenGLWidget()
{
	delete trackball;
	delete sceneGraph;
}


void OpenGLWidget::initializeGL()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClearDepth(1.0);
	glEnable(GL_DEPTH_TEST);

	// set lighting

	GLfloat ambientLight[4] = { 0.1, 0.1, 0.1, 0.1 };
	GLfloat diffuseLight[4] = { 0.7, 0.7, 0.7, 0.7 };
	GLfloat lightPosition[4] = { 0.0, 0.0, 6.0, 0.0 };
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_NORMALIZE);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
}

void OpenGLWidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	GLUquadric *sphere = gluNewQuadric();

	glLoadIdentity();
	glColor3f(0.0, 1.0, 0.0);
	glTranslated(trackball->rotate_center.x, trackball->rotate_center.y, trackball->rotate_center.z);
	gluSphere(sphere, 0.01, 30, 30);

	glLoadIdentity();
	glColor3f(0.0, 0.0, 1.0);
	glTranslated(trackball->zoom_center.x, trackball->zoom_center.y, trackball->zoom_center.z);
	gluSphere(sphere, 0.01, 30, 30);

	gluDeleteQuadric(sphere);

	trackball->apply();
	glColor3f(0.7, 0.7, 0.7);
// 	glBegin(GL_TRIANGLES);
// 	glVertex3d(-0.5, -0.5, 0.0);
// 	glVertex3d(0.5, -0.5, 0.0);
// 	glVertex3d(0.0, 0.5, 0.0);
// 	glEnd();

	sceneGraph->Render();
}

void OpenGLWidget::resizeGL(int width, int height)
{
	trackball->reAdjustTrackBall(width, height);

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -(double)height / (double)width, (double)height / (double)width, -1000.0, 1000.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void OpenGLWidget::mouseMoveEvent(QMouseEvent* event)
{
	trackball->mouseMove(event->buttons(), Vector2D(event->x(), event->y()));
	updateGL();
}

void OpenGLWidget::mousePressEvent(QMouseEvent* event)
{
	glMatrixMode(GL_MODELVIEW);
	double mv_matrix[16], proj_matrix[16];
	int viewport[4];
	glGetDoublev(GL_MODELVIEW_MATRIX, mv_matrix);
	glGetDoublev(GL_PROJECTION_MATRIX, proj_matrix);
	glGetIntegerv(GL_VIEWPORT, viewport);

	Vector3D picked_pos_, picked_pos;
	GLfloat winX = event->x(), winY = viewport[3] - event->y(), winZ;
	glReadPixels(winX, winY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);
	gluUnProject(winX, winY, winZ, 
		mv_matrix, proj_matrix, viewport, 
		&picked_pos_.x, &picked_pos_.y, &picked_pos_.z);

	picked_pos.x = mv_matrix[0] * picked_pos_.x + mv_matrix[4] * picked_pos_.y + mv_matrix[8] * picked_pos_.z + mv_matrix[12];
	picked_pos.y = mv_matrix[1] * picked_pos_.x + mv_matrix[5] * picked_pos_.y + mv_matrix[9] * picked_pos_.z + mv_matrix[13];
	picked_pos.z = mv_matrix[2] * picked_pos_.x + mv_matrix[6] * picked_pos_.y + mv_matrix[10] * picked_pos_.z + mv_matrix[14];

	trackball->mouseClick(event->buttons(), 
		1, 
		Vector2D(event->x(), event->y()), picked_pos);
	updateGL();
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