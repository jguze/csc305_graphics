/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Wed Oct 1 16:42:03 2014
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QTextEdit>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>
#include <basicopenglview.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QGridLayout *gridLayout;
    BasicOpenGLView *oglwidget;
    QGroupBox *groupBox;
    QPushButton *pushButton;
    QLineEdit *translateFieldX;
    QLineEdit *rotateField;
    QPushButton *rotateButton;
    QPushButton *undoButton;
    QPushButton *translateButton;
    QPushButton *scaleButton;
    QLineEdit *scaleFieldX;
    QLineEdit *translateFieldY;
    QLineEdit *scaleFieldY;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QPushButton *undoButton_2;
    QLineEdit *mField1;
    QLineEdit *mField2;
    QLineEdit *mField3;
    QLineEdit *mField6;
    QLineEdit *mField5;
    QLineEdit *mField4;
    QLineEdit *mField9;
    QLineEdit *mField8;
    QLineEdit *mField7;
    QTextEdit *currentStack;
    QLabel *label_6;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(785, 680);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        oglwidget = new BasicOpenGLView(centralWidget);
        oglwidget->setObjectName(QString::fromUtf8("oglwidget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(oglwidget->sizePolicy().hasHeightForWidth());
        oglwidget->setSizePolicy(sizePolicy);
        oglwidget->setStyleSheet(QString::fromUtf8("background-color: rgb(192, 193, 186);"));

        gridLayout->addWidget(oglwidget, 0, 0, 1, 1);

        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setMaximumSize(QSize(125, 590));
        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(0, 30, 114, 32));
        translateFieldX = new QLineEdit(groupBox);
        translateFieldX->setObjectName(QString::fromUtf8("translateFieldX"));
        translateFieldX->setGeometry(QRect(40, 60, 61, 22));
        rotateField = new QLineEdit(groupBox);
        rotateField->setObjectName(QString::fromUtf8("rotateField"));
        rotateField->setGeometry(QRect(50, 160, 51, 22));
        rotateButton = new QPushButton(groupBox);
        rotateButton->setObjectName(QString::fromUtf8("rotateButton"));
        rotateButton->setGeometry(QRect(0, 180, 110, 32));
        undoButton = new QPushButton(groupBox);
        undoButton->setObjectName(QString::fromUtf8("undoButton"));
        undoButton->setGeometry(QRect(0, 560, 110, 32));
        translateButton = new QPushButton(groupBox);
        translateButton->setObjectName(QString::fromUtf8("translateButton"));
        translateButton->setGeometry(QRect(0, 110, 110, 32));
        scaleButton = new QPushButton(groupBox);
        scaleButton->setObjectName(QString::fromUtf8("scaleButton"));
        scaleButton->setGeometry(QRect(0, 270, 110, 32));
        scaleFieldX = new QLineEdit(groupBox);
        scaleFieldX->setObjectName(QString::fromUtf8("scaleFieldX"));
        scaleFieldX->setGeometry(QRect(40, 220, 61, 22));
        translateFieldY = new QLineEdit(groupBox);
        translateFieldY->setObjectName(QString::fromUtf8("translateFieldY"));
        translateFieldY->setGeometry(QRect(40, 90, 61, 22));
        scaleFieldY = new QLineEdit(groupBox);
        scaleFieldY->setObjectName(QString::fromUtf8("scaleFieldY"));
        scaleFieldY->setGeometry(QRect(40, 250, 61, 22));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 60, 31, 16));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 220, 31, 16));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 250, 31, 16));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(20, 90, 31, 16));
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(10, 160, 51, 20));
        undoButton_2 = new QPushButton(groupBox);
        undoButton_2->setObjectName(QString::fromUtf8("undoButton_2"));
        undoButton_2->setGeometry(QRect(0, 400, 110, 32));
        mField1 = new QLineEdit(groupBox);
        mField1->setObjectName(QString::fromUtf8("mField1"));
        mField1->setGeometry(QRect(10, 310, 31, 22));
        mField2 = new QLineEdit(groupBox);
        mField2->setObjectName(QString::fromUtf8("mField2"));
        mField2->setGeometry(QRect(50, 310, 31, 22));
        mField3 = new QLineEdit(groupBox);
        mField3->setObjectName(QString::fromUtf8("mField3"));
        mField3->setGeometry(QRect(90, 310, 31, 22));
        mField6 = new QLineEdit(groupBox);
        mField6->setObjectName(QString::fromUtf8("mField6"));
        mField6->setGeometry(QRect(90, 340, 31, 22));
        mField5 = new QLineEdit(groupBox);
        mField5->setObjectName(QString::fromUtf8("mField5"));
        mField5->setGeometry(QRect(50, 340, 31, 22));
        mField4 = new QLineEdit(groupBox);
        mField4->setObjectName(QString::fromUtf8("mField4"));
        mField4->setGeometry(QRect(10, 340, 31, 22));
        mField9 = new QLineEdit(groupBox);
        mField9->setObjectName(QString::fromUtf8("mField9"));
        mField9->setGeometry(QRect(90, 370, 31, 22));
        mField8 = new QLineEdit(groupBox);
        mField8->setObjectName(QString::fromUtf8("mField8"));
        mField8->setGeometry(QRect(50, 370, 31, 22));
        mField7 = new QLineEdit(groupBox);
        mField7->setObjectName(QString::fromUtf8("mField7"));
        mField7->setGeometry(QRect(10, 370, 31, 22));
        currentStack = new QTextEdit(groupBox);
        currentStack->setObjectName(QString::fromUtf8("currentStack"));
        currentStack->setGeometry(QRect(10, 440, 111, 101));
        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(10, 540, 62, 16));

        gridLayout->addWidget(groupBox, 0, 1, 1, 1);


        horizontalLayout->addLayout(gridLayout);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 785, 22));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);
        QObject::connect(pushButton, SIGNAL(clicked()), MainWindow, SLOT(close()));
        QObject::connect(undoButton, SIGNAL(clicked()), oglwidget, SLOT(undo()));
        QObject::connect(translateButton, SIGNAL(clicked()), MainWindow, SLOT(translate()));
        QObject::connect(rotateButton, SIGNAL(clicked()), MainWindow, SLOT(rotate()));
        QObject::connect(scaleButton, SIGNAL(clicked()), MainWindow, SLOT(scale()));
        QObject::connect(undoButton_2, SIGNAL(clicked()), MainWindow, SLOT(applyMatrix()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("MainWindow", "Controls", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("MainWindow", "quit", 0, QApplication::UnicodeUTF8));
        rotateButton->setText(QApplication::translate("MainWindow", "rotate", 0, QApplication::UnicodeUTF8));
        undoButton->setText(QApplication::translate("MainWindow", "Pop Matrix", 0, QApplication::UnicodeUTF8));
        translateButton->setText(QApplication::translate("MainWindow", "translate", 0, QApplication::UnicodeUTF8));
        scaleButton->setText(QApplication::translate("MainWindow", "scale", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "x:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "x:", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindow", "y:", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("MainWindow", "y:", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("MainWindow", "angle:", 0, QApplication::UnicodeUTF8));
        undoButton_2->setText(QApplication::translate("MainWindow", "Push Matrix", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("MainWindow", "Stack", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
