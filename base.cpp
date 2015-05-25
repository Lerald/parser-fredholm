#include "base.h"
#include "stdio.h"
#include <QMessageBox>

extern QHash<QString, fdu> *funcs;

Base::Base(Base *firstOperand, Base *secondOperand)
{
    left = firstOperand;
    rigth = secondOperand;
    negative = false;
}

Base::~Base()
{
    if(left)
        delete left;

    if(rigth)
        delete rigth;
}



//-------------------------
Sum::Sum(Base *firstOperand, Base *secondOperand) :
    Base(firstOperand, secondOperand)
{
    fprintf(stderr, "Sum");
}

double Sum::calculation()
{
    double t = left->calculation() + rigth->calculation();
    std::cerr << t << " ";
    return t;
}
//-------------------------



Diff::Diff(Base *firstOperand, Base *secondOperand) :
    Base(firstOperand, secondOperand)
{
    fprintf(stderr, "Diff");
}

double Diff::calculation()
{
    return left->calculation() - rigth->calculation();
}
//-------------------------



Multi::Multi(Base *firstOperand, Base *secondOperand) :
    Base(firstOperand, secondOperand)
{
    fprintf(stderr, "Multi");
}

double Multi::calculation()
{
    return left->calculation() * rigth->calculation();
}
//-------------------------



Fraction::Fraction(Base *firstOperand, Base *secondOperand) :
    Base(firstOperand, secondOperand)
{
    fprintf(stderr, "Fract");
}

double Fraction::calculation()
{
    return left->calculation() / rigth->calculation();
}
//-------------------------



Power::Power(Base *firstOperand, Base *secondOperand) :
    Base(firstOperand, secondOperand)
{
    fprintf(stderr, "Power");
}

double Power::calculation()
{
    return pow(left->calculation(), rigth->calculation());
}
//-------------------------



Variable::Variable(QString name)
{
    fprintf(stderr, "Var %c ",name.toStdString().at(0));
    std::cout << name.toStdString();
    varName = name;
}

double Variable::calculation()
{
    double t = 0;
    if(head)
        t = head->getVariable(varName);
    else
        std::cerr << "Error";
    std::cerr << t;
    return t;
}
//-------------------------



Number::Number(double num)
{
    fprintf(stderr, "Num");
    number = num;
}

double Number::calculation()
{
    return number;
}
//-------------------------

Func_OneParam::Func_OneParam(QString *name, Base *firstOperand) :
    Base(firstOperand)
{
    funcName = "";
    funcName = *name;
    supported = funcs && funcs->contains(funcName);

    if(supported)
    {
        std_func = (funcs->value(funcName));
    }
}

double Func_OneParam::error(double param)
{
    fprintf(stderr, "Error func for param %f ", param);
    QMessageBox msgBox;
    msgBox.setText("Occurs error with call math func" + funcName);
    msgBox.exec();
    return 0;
}

double Func_OneParam::calculation()
{
    if(supported)
        return std_func(left->calculation());
    else
        return error(left->calculation());
}
//-------------------------

Func_TwoParam::Func_TwoParam(QString *name, Base *firstOperand, Base *secondOperand) :
    Base(firstOperand, secondOperand)
{
    funcName = "";
    funcName = *name;
    funcCase = 0;

    if(funcName == "fmax")
    {
        std_func = std::ptr_fun(fmax);
        funcCase = 1;
    }
    else if(funcName == "fmin")
    {
        std_func = std::ptr_fun(fmin);
        funcCase = 1;
    }
    else if(funcName == "modf")
    {
        funcCase = 2;
    }
    else if(funcName == "frexp")
    {
        funcCase = 3;
    }
    else if(funcName == "ldexp")
    {
        funcCase = 4;
    }
}

double Func_TwoParam::error(double first, double second)
{
    fprintf(stderr, "Error func for param %f and  %f", first, second);
    QMessageBox msgBox;
    msgBox.setText("Occurs error with call math func" + funcName);
    msgBox.exec();
    return 0;
}

double Func_TwoParam::calculation()
{
    double tmp = rigth->calculation();
    switch(funcCase)
    {
    case 1:
        return std_func(left->calculation(), tmp);
    case 2:
        return modf(left->calculation(), &tmp);
    case 3:
    {
        int integer = (int)tmp;
        return frexp(left->calculation(), &integer);
    }
    case 4:
        return ldexp(left->calculation(), (int)tmp);
    default:
        return error(left->calculation(), rigth->calculation());
    }

}

