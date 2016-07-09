#include "GOLWidget.h"
#include <QPainter>
#include <QColor>

GOLWidget::GOLWidget(QWidget *parent) :
    QWidget(parent)
{
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
