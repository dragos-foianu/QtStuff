#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{
    currentFile = "";
    ui->textEdit->setPlainText("");
}

void MainWindow::on_actionOpen_triggered()
{
    QString openFileName = QFileDialog::getOpenFileName(this, "Open file");
    if (!openFileName.isEmpty())
    {
        QFile qFile(openFileName);

        if (qFile.open(QFile::ReadOnly | QFile::Text))
        {
            currentFile = openFileName;
            QTextStream in(&qFile);
            QString text = in.readAll();
            qFile.close();

            ui->textEdit->setPlainText(text);
        }
    }
}

void MainWindow::on_actionSave_triggered()
{
    if (currentFile.isEmpty())
    {
        on_actionSave_As_triggered();
    }

    QRegExp regex(".*\.txt");
    if (!regex.exactMatch(currentFile))
    {
        currentFile.append(".txt");
    }

    QFile qFile(currentFile);
    if (qFile.open(QFile::WriteOnly | QFile::Text))
    {
        QTextStream out(&qFile);

        out << ui->textEdit->toPlainText();

        qFile.flush();
        qFile.close();
    }
}

void MainWindow::on_actionSave_As_triggered()
{
    QString saveFileName = QFileDialog::getSaveFileName(this, "Save file as");
    if (!saveFileName.isEmpty())
    {
        currentFile = saveFileName;
        on_actionSave_triggered();
    }
}

void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}

void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}
