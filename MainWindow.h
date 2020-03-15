#ifndef SOLDIER_APP_MAINWINDOW_H
#define SOLDIER_APP_MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets/QSlider>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void saveFile();

private:
    Ui::MainWindow *ui;

    int getValueFromSlider(QSlider *qSlider) const;
};
#endif // SOLDIER_APP_MAINWINDOW_H