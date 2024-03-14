#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <CoordinateSystem.cpp>
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene();
    CoordinateSystem *coords = new CoordinateSystem();
    //scene->addWidget(coords);
    ui->graphicsView->setScene(scene);
    //ui->widget = coords;
    //coords->setGeometry(9, 9, 800, 439);
    QGraphicsProxyWidget *proxy = scene->addWidget(coords);
    proxy->resize(887, 439);
    scene->update();
    //ui->gridLayout_2->addWidget(coords);
    //coords->show();

    // связываем сигнал нажатия кнопки со слотом
    QObject::connect(ui->pushButton_Draw, SIGNAL(clicked()), this, SLOT(event_PressDraw()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::event_PressDraw()
{

    QPainter painter(this);

    int width = size().width();
    int height = size().height();
    QPointF center = rect().center();

    painter.drawLine(0, center.y(), width, center.y()); // Ось X
    painter.drawLine(center.x(), 0, center.x(), height); // Ось Y
    // получаем координаты из окон ввода
    int x1 = ui->x1->text().toInt();
    int y1 = ui->y1->text().toInt();
    int x2 = ui->x2->text().toInt();
    int y2 = ui->y2->text().toInt();
    int x3 = ui->x3->text().toInt();
    int y3 = ui->y3->text().toInt();

    // скидываем координаты в список
    data << x1 << y1 << x2 << y2 << x3 << y3;

    QPolygon triangle;
    QPoint p1, p2, p3;
    QPen pen(Qt::red);
    pen.setWidth(2);
    QBrush brush(Qt::yellow);

    triangle.clear();

    //получили точки треугольника
    p1.setX(data.at(0));
    p1.setY(data.at(1));
    p2.setX(data.at(2));
    p2.setY(data.at(3));
    p3.setX(data.at(4));
    p3.setY(data.at(5));

    //поставили точки треугольника
    triangle << p1 << p2 << p3;

    //нарисовали треугольник
    scene->addPolygon(triangle, pen, brush);
    pen.setColor(Qt::black);
    scene->addLine(center.x(), 0, center.x(), height, pen);
    scene->addLine(center.x(), 0, center.x(), height, pen);
    //перерисовываем форму
    this->repaint();

    data.clear();
}


