#include <QtCore/QDebug>
#include "MainWindow.h"
#include "./ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent)
        , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->saveButton, SIGNAL(clicked()), this, SLOT(saveFile()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::saveFile() {
    int redValue = getValueFromSlider(ui->redSlider);
    int greenValue = getValueFromSlider(ui->greenSlider);
    int blueValue = getValueFromSlider(ui->blueSlider);
    qDebug() << redValue << " " << greenValue << " " << blueValue;
}

int MainWindow::getValueFromSlider(QSlider *qSlider) const {
    return qSlider->value(); }

