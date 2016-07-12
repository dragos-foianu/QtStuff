#include "GOLWidget.h"
#include <QPainter>
#include <QColor>

GOLWidget::GOLWidget(QWidget *parent) :
    QWidget(parent),
    timer(new QTimer()),
    gen(0),
    pop(0),
    cellSize(12),
    evos(-1)
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

    double horizontalSpacing = ((double) width()) / (width() / cellSize);
    for (double i = horizontalSpacing; i <= width(); i += horizontalSpacing) {
        p.drawLine(i, 0, i, height());
    }

    double verticalSpacing = ((double) height()) / (height() / cellSize);
    for (double i = verticalSpacing; i <= height(); i += verticalSpacing) {
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
    qDebug() << "GOLWidget::evolve()";
    timer->start();
}

void GOLWidget::pause()
{
    qDebug() << "GOLWidget::pause()";
    timer->stop();
}

void GOLWidget::reset()
{
    qDebug() << "GOLWidget::reset()";
    timer->stop();
    gen = 0;
    pop = 0;
    signalMetadataChanged();
}

void GOLWidget::setCellSize(QString csize)
{
    int size = csize.toInt();
    if (size < 5) {
        qDebug() << "GOLWidget::setCellSize(" << size << ") bad input";
    } else {
        qDebug() << "GOLWidget::setCellSize(" << size << ") successful";
        cellSize = size;
        this->update();
    }
    signalMetadataChanged();
}

void GOLWidget::setDelay(QString msec)
{
    int delay = msec.toInt();
    if (delay < 1) {
        qDebug() << "GOLWidget::setDelay(" << delay << ") bad input";
    } else {
        qDebug() << "GOLWidget::setDelay(" << delay << ") successful";
        timer->setInterval(delay);
    }
    signalMetadataChanged();
}

void GOLWidget::setEvolutions(QString evolutions)
{
    int evols = evolutions.toInt();
    if (evols == 0) {
        qDebug() << "GOLWidget::setEvolutions(" << evols << ") infinite";
        evos = -1;
    } else {
        qDebug() << "GOLWidget::setEvolutions(" << evols << ") successful";
        evos = evols;
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

int GOLWidget::evolutions()
{
    return evos;
}
