#ifndef COREFUNC_H
#define COREFUNC_H

#include <QMap>
#include <QString>
#include "math.h"
#include <functional>
#include <QHash>

typedef  std::pointer_to_unary_function<double,double>fdu;

void initStdFunction();

class Base;

class coreFunc
{
public:
    coreFunc(QString text);

    double getVariable (QString name);
    double getResult();

    //перенести в protected
    Base *expression;
    QMap<QString, double> variables;
    QString currFuncString;

private:


};

#endif // COREFUNC_H
