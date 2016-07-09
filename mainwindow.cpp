#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "injector.h"
#include <QListWidget>
#include <QString>
#include <QFileDialog>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->selectedProcess->setText(QString("Select a process"));
    on_refreshButton_clicked();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_injectButton_clicked()
{
    QString dllFile = QFileDialog::getOpenFileName(this, "Select DLL");

    if (ui->processList->selectedItems().size() == 1)
    {
        QString selected = ui->processList->selectedItems()[0]->text();
        Injector::injectDLL(Injector::getProcessHandle((char *) selected.toStdString().c_str()), dllFile.toStdString().c_str());

        ui->selectedProcess->setText(selected);
        ui->selectedProcess->repaint();
        return;
    }

    ui->selectedProcess->setText(QString("Select a process"));
}

void MainWindow::on_refreshButton_clicked()
{
    ui->processList->clear();
    std::vector<std::string> processList(Injector::listProcesses());

    /* No duplicates please, we're only selecting based on process name */
    std::sort(processList.begin(), processList.end());
    processList.erase(std::unique(processList.begin(), processList.end()), processList.end());

    for (std::vector<std::string>::iterator it = processList.begin(); it != processList.end() ; it++)
    {
        ui->processList->addItem(QString::fromStdString(*it));
    }

    ui->selectedProcess->setText(QString("Select a process"));
}
