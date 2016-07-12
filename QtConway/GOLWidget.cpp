#include "GOLWidget.h"
#include <QPainter>
#include <QColor>

GOLWidget::GOLWidget(QWidget *parent) :
    QWidget(parent),
    timer(new QTimer()),
    gen(0),
    pop(0),
    cellSize(12)
{
    timer->setInterval(1000);
    /* Timer timeout means new evolution */
    connect(timer, SIGNAL(timeout()), this, SLOT(processEvolution()));
    connect(this, SIGNAL(signalMetadataChanged()), parent, SLOT(updateMetadata()));
}

GOLWidget::~GOLWidget()
{
}

void GOLWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    paintGrid(painter);
}

void GOLWidget::paintGrid(QPainter &p)
{
    double top = 0, bottom = height() - 1;
    double left = 0, right = width() - 1;

    QRect grid(left, top, right, bottom);
    QColor gridColor = QColor("#a00");
    gridColor.setAlpha(30);
    p.setPen(gridColor);

    double horizontalSpacing = ((double) width()) / (width() / 12);
    for (double i = horizontalSpacing; i <= width(); i += horizontalSpacing)
    {
        p.drawLine(i, 0, i, height());
    }

    double verticalSpacing = ((double) height()) / (height() / 12);
    for (double i = verticalSpacing; i <= height(); i += verticalSpacing)
    {
        p.drawLine(0, i, width(), i);
    }

    gridColor.setAlpha(100);
    p.setPen(gridColor);

    p.drawLine(left, top, left, bottom);
    p.drawLine(left, top, right, top);
    p.drawLine(right, bottom, left, bottom);
    p.drawLine(right, bottom, right, top);

    p.drawRect(grid);
}

void GOLWidget::processEvolution()
{
    gen++;
    signalMetadataChanged();
}

void GOLWidget::evolve()
{
    qDebug() << "Evolve";
    timer->start();
}

void GOLWidget::pause()
{
    qDebug() << "Pause";
    timer->stop();
}

void GOLWidget::reset()
{
    qDebug() << "Reset";
    timer->stop();
    gen = 0;
    pop = 0;
    signalMetadataChanged();
}

void GOLWidget::setCellSize(QString csize)
{
    int size = csize.toInt();
    if (size < 5)
    {
        qDebug() << "Set size = \"5\"";
        cellSize = 5;
    }
    else
    {
        qDebug() << "Set cellsize = " << size;
        cellSize = size;
    }
    signalMetadataChanged();
}

void GOLWidget::setDelay(QString msec)
{
    int delay = msec.toInt();
    if (delay < 1)
    {
        qDebug() << "Set delay = \"1\" msec";
        timer->setInterval(1);
    }
    else
    {
        qDebug() << "Set delay = " << msec << " msec";
        timer->setInterval(delay);
    }
    signalMetadataChanged();
}

int GOLWidget::delay()
{
    return timer->interval();
}

int GOLWidget::generations()
{
    return gen;
}

int GOLWidget::population()
{
    return pop;
}

int GOLWidget::cellsize()
{
    return cellSize;
}
