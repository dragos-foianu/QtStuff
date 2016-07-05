#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->textEdit->setText(QString("NoProcess.exe"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_injectButton_clicked()
{
    qDebug() << "Injecting!";
}

void MainWindow::on_refreshButton_clicked()
{
    qDebug() << "Refreshing!";
}
