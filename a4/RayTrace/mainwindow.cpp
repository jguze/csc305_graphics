#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->openGLWidget->setImageViewer(ui->imageViewer);
    ui->openGLWidget->setProgressBar(ui->progressBar);
    ui->materialComboBox->setOpenGLWidget(ui->openGLWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent * e)
{
    ui->openGLWidget->handleKeyPress(e);
}
