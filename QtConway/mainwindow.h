#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "GOLWidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void updateMetadata();
    void delayEdited();
    void cellsizeEdited();
    void evolutionsEdited();

private:
    Ui::MainWindow *ui;
    GOLWidget *gol;
};

#endif // MAINWINDOW_H
