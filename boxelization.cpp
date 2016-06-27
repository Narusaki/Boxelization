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
	timer->setInterval(refreshTimeSlice);
	connect(timer, SIGNAL(timeout()), glWidget, SLOT(timeUp()));


	connect(optionWidgetUI->pushButton, SIGNAL(clicked()), this, SLOT(ResetAnimation()));
	connect(optionWidgetUI->pushButton_2, SIGNAL(clicked()), timer, SLOT(start()));
	connect(optionWidgetUI->pushButton_3, SIGNAL(clicked()), timer, SLOT(stop()));

	connect(optionWidgetUI->horizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(SetRotateSpeed(int)));
	// initially, set the rotation of 90 degrees completed in 5 seconds;
	SetRotateSpeed(optionWidgetUI->horizontalSlider->value());
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

void Boxelization::ResetAnimation()
{
	timer->stop();
	glWidget->sceneGraph->curPathInfoIndex = 0;
	glWidget->sceneGraph->rotateAngle = 0.0;
	for (auto &node : glWidget->sceneGraph->nodes)
	{
		for (int i = 0; i < 16; ++i)
			node.mvMatrix[i] = i % 5 == 0 ? 1 : 0;
	}
}