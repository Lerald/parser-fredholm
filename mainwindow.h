#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "corefunc.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_calculation_PB_clicked();

private:
    void compileFunc();
    void buildResultTable();
    coreFunc *function;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
