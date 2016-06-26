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
	
	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), glWidget, SLOT(timeUp()));

	timer->start(refreshTimeSlice);
	// initially, set the rotation of 90 degrees completed in 5 seconds;
	SetRotateSpeed(5);

	connect(optionWidgetUI->horizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(SetRotateSpeed(int)));
}

Boxelization::~Boxelization()
{
	delete glWidget;
	delete optionWidget;
	delete optionWidgetUI;

	delete timer;
}

void Boxelization::SetRotateSpeed(int periodTime)
{
	glWidget->sceneGraph->SetRotateSpeed(90.0 / (double)periodTime / 1000.0 * refreshTimeSlice);
}
