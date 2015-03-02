#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    animationTimer(NULL)
{
    ui->setupUi(this);

    // we create a simple timer, with the widget being its parent
    animationTimer = new QTimer(this);
    // the timer will send a signal timeout at regular intervals.
    // whenever this timeout signal occurs, we want it to call our drawOpenGL
    // function
    animateon=false;
    transformon=false;
    connect(animationTimer, SIGNAL(timeout()), this, SLOT(drawOpenGL()));
    // we start the timer with a timeout interval of 20ms
//    animationTimer->start(20);

    matrixFields[0][0] = ui->mField1;
    matrixFields[0][1] = ui->mField2;
    matrixFields[0][2] = ui->mField3;
    matrixFields[1][0] = ui->mField4;
    matrixFields[1][1] = ui->mField5;
    matrixFields[1][2] = ui->mField6;
    matrixFields[2][0] = ui->mField7;
    matrixFields[2][1] = ui->mField8;
    matrixFields[2][2] = ui->mField9;
    ui->oglwidget->setStackViewer(ui->currentStack);
}

void MainWindow::drawOpenGL()
{
    // whenever drawOpenGL gets called, we only want to repaint our opengl widget
    ui->oglwidget->repaint();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::animate()
{
    animateon = !animateon;
    //ui->oglwidget->setanimate(animateon);
}

void MainWindow::translate()
{
    bool checkX, checkY;
    double x, y;
    x = ui->translateFieldX->text().toDouble(&checkX);
    y = ui->translateFieldY->text().toDouble(&checkY);
    if (!checkX || !checkY)
    {
        qDebug() << "Invalid field";
    } else
    {
        ui->oglwidget->translate(x, y);
    }
}

void MainWindow::rotate()
{
    bool check;
    double angle = ui->rotateField->text().toDouble(&check);
    if (!check)
    {
        qDebug() << "Invalid angle";
    } else {
         ui->oglwidget->rotate(angle);
    }
}

void MainWindow::scale()
{
    bool checkX, checkY;
    double x, y;
    x = ui->scaleFieldX->text().toDouble(&checkX);
    y = ui->scaleFieldY->text().toDouble(&checkY);
    if (!checkX || !checkY)
    {
        qDebug() << "Invalid field";
    } else
    {
        ui->oglwidget->scale(x, y);
    }
}

void MainWindow::applyMatrix()
{
    double m[3][3];
    bool check;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            m[i][j] = matrixFields[i][j]->text().toDouble(&check);
            if (!check)
            {
                qDebug() << "Invalid field at" << i << j;
                return;
            }
        }
    }
    ui->oglwidget->applyMatrix(m);
}
