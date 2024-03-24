#ifndef COORDINATESYSTEM_H
#define COORDINATESYSTEM_H

#include <QWidget>

class CoordinateSystem : public QWidget
{
    Q_OBJECT
public:
    explicit CoordinateSystem(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event) override;
    void drawFigure(QPainter &painter);
    void drawScale(QPainter &painter, int width, int height);
    void drawAxisLabels(QPainter &painter, int width, int height);
    void drawGrid(QPainter &painter, int width, int height);
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event);
    void setPoint(int point);
private:
    int scale;
    int pointRadius;
    QPoint center;
    QVector<int> points;
    QPoint dragStart;
    bool isDragging;
signals:
};

#endif // COORDINATESYSTEM_H
