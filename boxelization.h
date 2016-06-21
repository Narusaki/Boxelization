#ifndef BOXELIZATION_H
#define BOXELIZATION_H

#include <QtWidgets/QMainWindow>
#include "ui_boxelization.h"
#include "ui_optionwidget.h"
#include "openglwidget.h"

class Boxelization : public QMainWindow
{
	Q_OBJECT

public:
	Boxelization(QWidget *parent = 0);
	~Boxelization();

private:
	Ui::BoxelizationClass ui;

	OpenGLWidget *glWidget;
	Ui::OptionWidget *optionWidgetUI;
	QDockWidget *optionWidget;
};

#endif // BOXELIZATION_H
