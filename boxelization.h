#ifndef BOXELIZATION_H
#define BOXELIZATION_H

#include <QtWidgets/QMainWindow>
#include "ui_boxelization.h"

class Boxelization : public QMainWindow
{
	Q_OBJECT

public:
	Boxelization(QWidget *parent = 0);
	~Boxelization();

private:
	Ui::BoxelizationClass ui;
};

#endif // BOXELIZATION_H
