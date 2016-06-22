#include "boxelization.h"

Boxelization::Boxelization(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	glWidget = new OpenGLWidget(this);
	setCentralWidget(glWidget);

	optionWidgetUI = new Ui::OptionWidget();
	optionWidget = new QDockWidget(this);
	optionWidgetUI->setupUi(optionWidget);
	optionWidget->setFocusPolicy(Qt::ClickFocus);
	optionWidget->setFeatures(QDockWidget::DockWidgetFloatable | QDockWidget::DockWidgetMovable);
	addDockWidget(Qt::LeftDockWidgetArea, optionWidget);
	
}

Boxelization::~Boxelization()
{
	delete glWidget;
	delete optionWidget;
	delete optionWidgetUI;
}
