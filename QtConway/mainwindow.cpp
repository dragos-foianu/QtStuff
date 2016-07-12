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
    connect(ui->delayEdit, SIGNAL(editingFinished()), this, SLOT(delayEdited()));
    connect(ui->sizeEdit, SIGNAL(editingFinished()), this, SLOT(cellsizeEdited()));
    connect(ui->evoEdit, SIGNAL(editingFinished()), this, SLOT(evolutionsEdited()));
    connect(ui->evolveButton, SIGNAL(clicked()), gol, SLOT(evolve()));
    connect(ui->pauseButton, SIGNAL(clicked()), gol, SLOT(pause()));
    connect(ui->resetButton, SIGNAL(clicked()), gol, SLOT(reset()));

    ui->gameLayout->addWidget(gol);
    updateMetadata();
}

void MainWindow::updateMetadata()
{
    qDebug() << "MainWindow::updateMetadata()";
    ui->genEdit->setText(QString::number(gol->generations()));
    ui->popEdit->setText(QString::number(gol->population()));
    ui->delayEdit->setText(QString::number(gol->delay()));
    ui->sizeEdit->setText(QString::number(gol->cellsize()));

    if (gol->evolutions() < 0) {
        ui->evoEdit->setText("Infinite");
    } else {
        ui->evoEdit->setText(QString::number(gol->evolutions()));
    }
}

void MainWindow::delayEdited()
{
    gol->setDelay(ui->delayEdit->text());
}

void MainWindow::cellsizeEdited()
{
    gol->setCellSize(ui->sizeEdit->text());
}

void MainWindow::evolutionsEdited()
{
    gol->setEvolutions(ui->evoEdit->text());
}

MainWindow::~MainWindow()
{
    delete ui;
}
