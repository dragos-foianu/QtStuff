#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "injector.h"
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
    Injector::injectDLL(Injector::getProcessHandle((char *) "chrome.exe"), "dllFile");
}

void MainWindow::on_refreshButton_clicked()
{
    qDebug() << "Refreshing!";
}
