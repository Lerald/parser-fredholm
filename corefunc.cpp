#include "corefunc.h"
#include "base.h"
#include "stdio.h"


coreFunc::coreFunc(QString text)
{
    currFuncString = text;
    variables.insert("x", 8);
    variables.insert("y", 2);
}

double coreFunc::getVariable (QString name)
{
    std::cerr << name.toStdString();
    if (variables.contains(name))
    {
        return variables.value(name, 0);
    }
    else
    {
        std::cerr << "Ошибка! Незаданная переменная.";
        return 0;
    }
}

double coreFunc::getResult()
{
    return expression->calculation();
}
