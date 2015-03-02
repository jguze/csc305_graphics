#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGroupBox>
#include "openGLwidget.h"
#include <QLabel>
#include <QGridLayout>
#include "flatwidget.h"
#include "flatwidgetxy.h"
#include "flatwidgetxz.h"
#include "flatwidgetyz.h"

#define STRAFE_AMOUNT 5;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:

public slots:
    void drawCylinder();
    void clear();
    void toggleSpecial(bool);
    void fullCylinder(bool);
    void dotCylinder(bool);
    void lineCylinder(bool);

    void shapeCircle(bool);
    void shapeSquare(bool);
    void shapeSpecial(bool);

    void changeRadius(int);
    void addLight();
    void drawCube(bool);
    void drawLids(bool);

protected:
    void timerEvent(QTimerEvent * );
    void keyPressEvent(QKeyEvent *);

private:
    Ui::MainWindow *ui;

    //Added layout elements
    QGridLayout * centralGridlayout;

    QGroupBox * mainViewBox;
    QBoxLayout * mainInnerLayout;
    OpenGLWidget * mainView;

    QGroupBox * xyViewBox;
    QBoxLayout * xyInnerLayout;
    OpenGLWidget * xyView;

    QGroupBox * xzViewBox;
    QBoxLayout * xzInnerLayout;
    OpenGLWidget * xzView;

    QGroupBox * yzViewBox;
    QBoxLayout * yzInnerLayout;
    OpenGLWidget * yzView;

};

#endif // MAINWINDOW_H
