#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "GOLWidget.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    gol(new GOLWidget(this))
{
    ui->setupUi(this);

    ui->centralWidget->setMinimumSize(1280, 780);
    ui->centralWidget->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));

    /* Setup slots */
    connect(ui->delayEdit, SIGNAL(textEdited(QString)), gol, SLOT(setDelay(QString)));
    connect(ui->sizeEdit, SIGNAL(textEdited(QString)), gol, SLOT(setCellSize(QString)));
    connect(ui->evolveButton, SIGNAL(clicked()), gol, SLOT(evolve()));
    connect(ui->pauseButton, SIGNAL(clicked()), gol, SLOT(pause()));
    connect(ui->resetButton, SIGNAL(clicked()), gol, SLOT(reset()));

    ui->gameLayout->addWidget(gol);
    updateMetadata();
}

void MainWindow::updateMetadata()
{
    qDebug() << "Updating universe data: gen = \"" << gol->generations() <<
                "\", pop = \"" << gol->population() << "\"";
    ui->genEdit->setText(QString::number(gol->generations()));
    ui->popEdit->setText(QString::number(gol->population()));
    ui->delayEdit->setText(QString::number(gol->delay()));
    ui->sizeEdit->setText(QString::number(gol->cellsize()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
