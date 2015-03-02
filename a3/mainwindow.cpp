#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    DataManager * dataManager = new DataManager();

    centralGridlayout = new QGridLayout();

    mainViewBox = new QGroupBox("3D View");
    mainViewBox->resize(420, 310);
    mainInnerLayout = new QBoxLayout(QBoxLayout::LeftToRight, mainViewBox);
    mainView = new OpenGLWidget(dataManager);
    mainView->updateGL();
    mainInnerLayout->addWidget(mainView);
    mainViewBox->setLayout(mainInnerLayout);
    centralGridlayout->addWidget(mainViewBox, 0, 0, 1, 1);

    xyViewBox = new QGroupBox("XY View");
    xyViewBox->resize(420, 310);
    xyInnerLayout = new QBoxLayout(QBoxLayout::LeftToRight, xyViewBox);
    xyView = new FlatWidgetXY(dataManager);
    xyInnerLayout->addWidget(xyView);
    xyViewBox->setLayout(xyInnerLayout);
    centralGridlayout->addWidget(xyViewBox, 0, 1, 1, 1);

    xzViewBox = new QGroupBox("XZ View");
    xzViewBox->resize(420, 310);
    xzInnerLayout = new QBoxLayout(QBoxLayout::LeftToRight, xzViewBox);
    xzView = new FlatWidgetXZ(dataManager);
    xzInnerLayout->addWidget(xzView);
    xzViewBox->setLayout(xzInnerLayout);
    centralGridlayout->addWidget(xzViewBox, 1, 0, 1, 1);

    yzViewBox = new QGroupBox("YZ View");
    yzViewBox->resize(420, 310);
    yzInnerLayout = new QBoxLayout(QBoxLayout::LeftToRight, yzViewBox);
    yzView = new FlatWidgetYZ(dataManager);
    yzInnerLayout->addWidget(yzView);
    yzViewBox->setLayout(yzInnerLayout);
    centralGridlayout->addWidget(yzViewBox, 1, 1, 1, 1);

    ui->viewWidget->setLayout(centralGridlayout);
    ui->cylinderRadius->setFocusPolicy(Qt::NoFocus);

    //Start the timer: running on 30 fps (33 ms per time-event)
    startTimer(33);
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::timerEvent(QTimerEvent *)
{
    //Post update() to all openGL viewports
    mainView->update();
    xyView->update();
    xzView->update();
    yzView->update();
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Left)
    {
        mainView->lookPrevPoint();
    } else if (e->key() == Qt::Key_Right)
    {
        mainView->lookNextPoint();
    } else if (e->key() == Qt::Key_W)
    {
        mainView->viewTo.z += STRAFE_AMOUNT;
    } else if (e->key() == Qt::Key_A)
    {
        mainView->viewTo.x -= STRAFE_AMOUNT;
    } else if (e->key() == Qt::Key_S)
    {
        mainView->viewTo.z -= STRAFE_AMOUNT;
    } else if (e->key() == Qt::Key_D)
    {
        mainView->viewTo.x += STRAFE_AMOUNT;
    } else if (e->key() == Qt::Key_Q)
    {
        mainView->viewTo.y -= STRAFE_AMOUNT;
    } else if (e->key() == Qt::Key_E)
    {
        mainView->viewTo.y += STRAFE_AMOUNT;
    } else if (e->key() == Qt::Key_1)
    {
        mainView->hideAxis();
    } else if (e->key() == Qt::Key_2)
    {
        mainView->hideGridXZ();
    } else if (e->key() == Qt::Key_3)
    {
        mainView->hideSpline();
    } else if (e->key() == Qt::Key_4)
    {
        mainView->hidePointLines();
    } else if (e->key() == Qt::Key_5)
    {
        mainView->hidePoints();
    } else if (e->key() == Qt::Key_6)
    {
        mainView->hideGrid();
    } else if (e->key() == Qt::Key_7)
    {
        mainView->hideGridXY();
    } else if (e->key() == Qt::Key_8)
    {
        mainView->hideGridYZ();
    } else if (e->key()  == Qt::Key_Up)
    {
        mainView->dataManager->catmullRom.tension += 0.1;
    } else if (e->key() == Qt::Key_Down)
    {
        mainView->dataManager->catmullRom.tension -= 0.1;
    }
}

void MainWindow::drawCylinder()
{
    mainView->drawCylinder();
    xyView->drawCylinder();
    xzView->drawCylinder();
    yzView->drawCylinder();
}

void MainWindow::clear()
{
    mainView->clear();
}

void MainWindow::toggleSpecial(bool on)
{
    mainView->toggleSpecial(on);
    xyView->toggleSpecial(on);
    xzView->toggleSpecial(on);
    yzView->toggleSpecial(on);
}

void MainWindow::fullCylinder(bool on)
{
    if (!on) return;
    mainView->cylinderType = TRIANGLE;
}

void MainWindow::dotCylinder(bool on)
{
    if (!on) return;
    mainView->cylinderType = VERTEX;
}

void MainWindow::lineCylinder(bool on)
{
    if (!on) return;
    mainView->cylinderType = LINE;
}

void MainWindow::shapeCircle(bool on)
{
    if (!on) return;
    mainView->shape = CIRCLE;
}

void MainWindow::shapeSquare(bool on)
{
    if (!on) return;
    mainView->shape = SQUARE;
}

void MainWindow::shapeSpecial(bool on)
{
    if (!on) return;
    mainView->shape = SPECIAL;
}

void MainWindow::changeRadius(int radius)
{
    mainView->cylinder_radius = (double)radius;
    xyView->cylinder_radius = (double)radius;
    xzView->cylinder_radius = (double)radius;
    yzView->cylinder_radius = (double)radius;
}

void MainWindow::addLight()
{
    mainView->addLight();
}

void MainWindow::drawCube(bool on)
{
    mainView->drawCube = xyView->drawCube = xzView->drawCube = yzView->drawCube = on;
}

void MainWindow::drawLids(bool on)
{
    mainView->drawLids = on;
}
