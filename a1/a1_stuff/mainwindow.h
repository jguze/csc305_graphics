#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QLineEdit>
#include <QTextEdit>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:

    /**
      * we use this slot to trigger our widget's redraw function
      * with the timer
      */
    void drawOpenGL();
    void animate();

    /**
     * @brief translate Invoked when the user hits the translate button
     */
    void translate();

    /**
     * @brief rotate Invoked when the user hits the rotate button
     */
    void rotate();

    /**
     * @brief scale Invoked when the user hits the scale button
     */
    void scale();

    /**
     * @brief applyMatrix Invoked when the user hits the 'Apply Matrix' button
     */
    void applyMatrix();

private:
    Ui::MainWindow *ui;

    QTimer * animationTimer;        /**< this is the only member so far added to the auto-generated mainwindow class. We use the timer for regular OpenGL redraws. */
    bool animateon, transformon;

    /**
     * @brief matrixFields A 3x3 array of the fields to input matrix values into
     */
    QLineEdit * matrixFields[3][3];

};

#endif // MAINWINDOW_H
