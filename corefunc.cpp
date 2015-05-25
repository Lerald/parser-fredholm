#include "corefunc.h"
#include "base.h"
#include "stdio.h"

QHash<QString, fdu> *funcs;

void initStdFunction()
{
    funcs = new QHash <QString, fdu>();
    funcs->insert("sin", std::ptr_fun(sin));
    funcs->insert("cos", std::ptr_fun(cos));
    funcs->insert("tan", std::ptr_fun(tan));
    funcs->insert("acos", std::ptr_fun(acos));
    funcs->insert("asin", std::ptr_fun(asin));
    funcs->insert("atan", std::ptr_fun(atan));

    funcs->insert("sinh", std::ptr_fun(sinh));
    funcs->insert("cosh", std::ptr_fun(cosh));
    funcs->insert("tanh", std::ptr_fun(tanh));
    funcs->insert("acosh", std::ptr_fun(acosh));
    funcs->insert("asinh", std::ptr_fun(asinh));
    funcs->insert("atanh", std::ptr_fun(atanh));

    funcs->insert("exp", std::ptr_fun(exp));
    funcs->insert("log", std::ptr_fun(log));
    funcs->insert("log10", std::ptr_fun(log10));
    funcs->insert("exp2", std::ptr_fun(exp2));
    funcs->insert("expm1", std::ptr_fun(expm1));
    funcs->insert("log2", std::ptr_fun(log2));

    funcs->insert("sqrt", std::ptr_fun(sqrt));
    funcs->insert("cbrt", std::ptr_fun(cbrt));
    funcs->insert("fabs", std::ptr_fun(fabs));
}

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
