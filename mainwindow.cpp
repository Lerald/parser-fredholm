#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gram_yacc.h"
#include "stdio.h"
#include "iostream"

extern QHash<QString, fdu> *funcs;

extern int calculate(char * str,  coreFunc * result);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->Steps_LE->setText("10");
    ui->Xmax_LE->setText("10");
    ui->Xmin_LE->setText("0");

    ui->Ymax_LE->setText("10");
    ui->Ymin_LE->setText("0");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::compileFunc()
{
    QString tmp = ui->lineEdit->text();
    if(tmp.isEmpty())
        return;

    tmp = QString("F(x,y)=") + tmp;
    function = new coreFunc(tmp);

    char *input = new char[tmp.length()];
    for(int i = 0; i < tmp.length(); i++)
    {
        input[i] = tmp.at(i).toLatin1();
    }
    calculate(input, function);
    std::cerr << function->getResult();

    delete[] input;
}

void MainWindow::buildResultTable()
{
    if(!function)
        return;

    double steps = ui->Steps_LE->text().toDouble();
    ui->tableWidget->setColumnCount(steps);
    ui->tableWidget->setRowCount(steps);
    double xMax = ui->Xmax_LE->text().toDouble();
    double xMin = ui->Xmin_LE->text().toDouble();
    double yMax = ui->Ymax_LE->text().toDouble();
    double yMin = ui->Ymin_LE->text().toDouble();

    double xShift = (xMax - xMin)/steps;
    double yShift = (yMax - yMin)/steps;
    for(double x = 0; x < steps; x++)
    {
        function->variables.insert("x", xMin + xShift*x);
        for(double y = 0; y < steps; y++)
        {
            function->variables.insert("y", yMin + yShift*y);
            QTableWidgetItem *item = new QTableWidgetItem(QString("%1").arg(function->getResult()));
            ui->tableWidget->setItem(y,x, item);
        }
    }
}

void MainWindow::on_calculation_PB_clicked()
{
    compileFunc();
    buildResultTable();
}
