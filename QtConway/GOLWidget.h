#ifndef GOLWIDGET_H
#define GOLWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QDebug>

class GOLWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GOLWidget(QWidget *parent = 0);
    ~GOLWidget();

protected:
    void paintEvent(QPaintEvent *);

private slots:
    void paintGrid(QPainter &p);
    void processEvolution();

public slots:
    void evolve();
    void pause();
    void reset();

    void setDelay(QString msec);
    void setCellSize(QString csize);
    void setEvolutions(QString evolutions);

public:
    int delay();
    int generations();
    int population();
    int evolutions();
    int cellsize();

signals:
    void signalMetadataChanged();

private:
    QTimer *timer;
    int gen;
    int pop;
    int evos;
    int cellSize;
    int currentEvo;
};

#endif // GOLWIDGET_H
