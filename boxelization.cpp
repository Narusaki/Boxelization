#include "boxelization.h"
#include <QtWidgets\QFileDialog>

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
	connect(optionWidgetUI->pushButton_4, SIGNAL(clicked()), this, SLOT(saveFrame()));
	connect(optionWidgetUI->horizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(SetRotateSpeed(int)));
	// initially, set the rotation of 90 degrees completed in 5 seconds;
	SetRotateSpeed(optionWidgetUI->horizontalSlider->value());

	connect(ui.actionImport, SIGNAL(triggered()), this, SLOT(LoadCubes()));
	connect(ui.actionLoad_Connectivity, SIGNAL(triggered()), this, SLOT(LoadConnectivity()));
	connect(ui.actionLoad_Path, SIGNAL(triggered()), this, SLOT(LoadPath()));
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
	glWidget->sceneGraph->SetRotateSpeed(90.0 / (double)periodTime * 10.0 / 1000.0 * refreshTimeSlice);
	//glWidget->sceneGraph->SetRotateSpeed(90.0 / (0.002 * (double)periodTime) / 1000.0 * refreshTimeSlice);
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
	glWidget->update();
}

void Boxelization::LoadCubes()
{
	QString dirName = QFileDialog::getExistingDirectory(this, "Choose Boxes Directory", "");
	glWidget->sceneGraph->LoadModel(dirName.toStdString());
}

void Boxelization::LoadConnectivity()
{
	QString filename = QFileDialog::getOpenFileName(this, "Open Connectivity File", "", "Connectivity file(*.connect)");
	glWidget->sceneGraph->LoadConnectivity(filename.toStdString());
}

void Boxelization::LoadPath()
{
	QString filename = QFileDialog::getOpenFileName(this, "Open Path File", "", "Path file(*.path)");
	glWidget->sceneGraph->LoadPath(filename.toStdString());
}

void Boxelization::saveFrame() {
	glWidget->sceneGraph->is_output_frame = !glWidget->sceneGraph->is_output_frame;
}