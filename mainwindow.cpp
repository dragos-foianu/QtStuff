#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "injector.h"
#include <QListWidget>
#include <QString>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->selectedProcess->setText(QString("Nothing injected."));
    on_refreshButton_clicked();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_injectButton_clicked()
{
    QString dllFile = QFileDialog::getOpenFileName(this, "Select DLL");
    Injector::injectDLL(Injector::getProcessHandle((char *) "chrome.exe"), dllFile.toStdString().c_str());
}

void MainWindow::on_refreshButton_clicked()
{
    std::vector<std::string> processList(Injector::listProcesses());

    /* No duplicates please, we're only selecting based on process name */
    std::sort(processList.begin(), processList.end());
    processList.erase(std::unique(processList.begin(), processList.end()), processList.end());

    for (std::vector<std::string>::iterator it = processList.begin(); it != processList.end() ; it++)
    {
        ui->processList->addItem(QString::fromStdString(*it));
    }
}
