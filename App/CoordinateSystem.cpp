#include "coordinatesystem.h"
#include <QtWidgets>

CoordinateSystem::CoordinateSystem(QWidget *parent) : QWidget(parent), scale(20), pointRadius(3), isDragging(false) {
    setMouseTracking(true);
    center = rect().center();
}

void CoordinateSystem::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    int width = size().width();
    int height = size().height();

    painter.drawLine(0, center.y(), width, center.y()); // Ось X
    painter.drawLine(center.x(), 0, center.x(), height); // Ось Y

    drawScale(painter, width, height);

    drawAxisLabels(painter, width, height);

    drawGrid(painter, width, height);

    drawFigure(painter);

    Q_UNUSED(event);



    //QPainterPath path;
    //path.addRect(center.x(), center.y(), 60, 10);
    //path.moveTo(center.x(), center.y());
    //path.cubicTo(99, 0,  50, 50,  99, 99);
    //path.cubicTo(0, 99,  50, 50,  0, 0);

    //painter.fillRect(0, 0, 100, 100, Qt::white);
    ///painter.setPen(QPen(QColor(79, 106, 25), 1, Qt::SolidLine,
                       // Qt::FlatCap, Qt::MiterJoin));
    //painter.setBrush(QColor(122, 163, 39));

   // painter.drawPath(path);
}

void CoordinateSystem::drawFigure(QPainter &painter)
{
    painter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap));
    painter.setBrush(QBrush(Qt::red, Qt::SolidPattern));
    //QPainterPath path;
    QPolygonF triangle;
    QPointF p;
    for(int i = 0; i < points.length(); i+=2)
    {
        p.setX(center.x() + points[i]*scale);
        p.setY(center.y() - points[i+1]*scale);
        triangle << p;
    }
    //path.addPolygon(triangle);
    //painter.drawPath(path);
    painter.drawConvexPolygon(triangle);
    triangle.clear();
}


void CoordinateSystem::drawScale(QPainter &painter, int width, int height) {
    const int step = scale;

    for (int x = center.x() + scale * step; x < width; x += scale * step)
        painter.drawLine(x, center.y() - 3, x, center.y() + 3);
    for (int x = center.x() - scale * step; x > 0; x -= scale * step)
        painter.drawLine(x, center.y() - 3, x, center.y() + 3);

    for (int y = center.y() + scale * step; y < height; y += scale * step)
        painter.drawLine(center.x() - 3, y, center.x() + 3, y);
    for (int y = center.y() - scale * step; y > 0; y -= scale * step)
        painter.drawLine(center.x() - 3, y, center.x() + 3, y);
}

void CoordinateSystem::drawAxisLabels(QPainter &painter, int width, int height) {
    QFontMetrics metrics(painter.font());
    int textHeight = metrics.height();

    for (int x = center.x() + scale; x < width; x += scale) {
        QString label = QString::number((x - center.x()) / scale);
        QRect boundingRect = metrics.boundingRect(label);
        int labelWidth = boundingRect.width();
        painter.drawText(x - labelWidth / 2, center.y() + textHeight + 10, label);
    }
    for (int x = center.x() - scale; x > 0; x -= scale) {
        QString label = QString::number((x - center.x()) / scale);
        QRect boundingRect = metrics.boundingRect(label);
        int labelWidth = boundingRect.width();
        painter.drawText(x - labelWidth / 2, center.y() + textHeight + 10, label);
    }

    for (int y = center.y() + scale; y < height; y += scale) {
        QString label = QString::number((center.y() - y) / scale);
        QRect boundingRect = metrics.boundingRect(label);
        int labelWidth = boundingRect.width();
        painter.drawText(center.x() - labelWidth - 10, y + textHeight / 2, label);
    }
    for (int y = center.y() - scale; y > 0; y -= scale) {
        QString label = QString::number((center.y() - y) / scale);
        QRect boundingRect = metrics.boundingRect(label);
        int labelWidth = boundingRect.width();
        painter.drawText(center.x() - labelWidth - 10, y + textHeight / 2, label);
    }

    QRect xAxisLabelRect = metrics.boundingRect("X");
    painter.drawText(width - xAxisLabelRect.width() - 3, center.y() + textHeight, "X");
    painter.drawText(center.x() + 5, textHeight, "Y");
}

void CoordinateSystem::drawGrid(QPainter &painter, int width, int height) {
    const int cellSize = scale;

    QPen gridPen(Qt::lightGray, 1, Qt::DashLine);
    painter.setPen(gridPen);

    for (int x = center.x() + cellSize; x < width; x += cellSize)
        painter.drawLine(x, 0, x, height);
    for (int x = center.x() - cellSize; x > 0; x -= cellSize)
        painter.drawLine(x, 0, x, height);

    for (int y = center.y() + cellSize; y < height; y += cellSize)
        painter.drawLine(0, y, width, y);
    for (int y = center.y() - cellSize; y > 0; y -= cellSize)
        painter.drawLine(0, y, width, y);
}

void CoordinateSystem::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        dragStart = event->pos();
        isDragging = true;
    }
}

void CoordinateSystem::mouseMoveEvent(QMouseEvent *event) {
    if (isDragging) {
        QPoint delta = event->pos() - dragStart;
        center -= delta;
        dragStart = event->pos();
        update();
    }
}

void CoordinateSystem::mouseReleaseEvent(QMouseEvent *event)  {
    if (event->button() == Qt::LeftButton) {
        isDragging = false;
    }
}

void CoordinateSystem::wheelEvent(QWheelEvent *event) {
    QPoint numDegrees = event->angleDelta() / 8;
    if (!numDegrees.isNull()) {
        QPoint numSteps = numDegrees / 15;
        scale += numSteps.y();
        if (scale < 1)
            scale = 1;
        update();
    }
    event->accept();
    //repaint();
}

void CoordinateSystem::setPoint(int point){points.append(point);}
