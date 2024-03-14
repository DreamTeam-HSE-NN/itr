#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
   // void paintEvent(QPaintEvent *event);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QList<int> data;
    int scale;
    int pointRadius;
    QPoint center;
    QVector<QPoint> points;
    QPoint dragStart;
    bool isDragging;

public slots:
    void event_PressDraw();

};
#endif // MAINWINDOW_H
