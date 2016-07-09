#ifndef GOLWIDGET_H
#define GOLWIDGET_H

#include <QWidget>

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
};

#endif // GOLWIDGET_H
