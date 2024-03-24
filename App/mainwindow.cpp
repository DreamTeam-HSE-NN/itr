#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <CoordinateSystem1.cpp>
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //scene = new QGraphicsScene();
    //CoordinateSystem *coords = new CoordinateSystem();
    //scene->addWidget(coords);
    //ui->graphicsView->setScene(scene);
    //ui->widget = coords;
    //coords->setGeometry(9, 9, 800, 439);
    //QGraphicsProxyWidget *proxy = scene->addWidget(coords);
    //proxy->resize(887, 439);
    //scene->update();
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

    int coordinates[6];
    coordinates[0] = ui->x1->text().toInt();
    coordinates[1] = ui->y1->text().toInt();
    coordinates[2] = ui->x2->text().toInt();
    coordinates[3] = ui->y2->text().toInt();
    coordinates[4] = ui->x3->text().toInt();
    coordinates[5] = ui->y3->text().toInt();
    //QPointF p;
    for(int i = 0; i < 6; ++i)
    {
        ui->widget->setPoint(coordinates[i]);
    }
    //ui->widget->update();

    //перерисовываем форму
    this->repaint();
}


