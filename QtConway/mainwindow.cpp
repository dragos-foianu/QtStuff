#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "GOLWidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    gol(new GOLWidget(this))
{
    ui->setupUi(this);

    ui->centralWidget->setMinimumSize(1280, 780);
    ui->centralWidget->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));

    ui->gameLayout->addWidget(gol);
}

MainWindow::~MainWindow()
{
    delete ui;
}
