#ifndef BASE_H
#define BASE_H

#include "corefunc.h"
#include "iostream"

//--------------------
class Base
{
public:
    Base(Base *firstOperand = 0, Base *secondOperand = 0);
    ~Base();
    virtual double calculation(){return 0;}

    //перенести в protected
    Base *left;
    Base *rigth;
    coreFunc *head;
    bool negative;
protected:


};

class Sum : public Base
{
public:
    Sum(Base *firstOperand = 0, Base *secondOperand = 0);
    double calculation();
};

class Diff : public Base
{
public:
    Diff(Base *firstOperand = 0, Base *secondOperand = 0);
    double calculation();
};

class Multi : public Base
{
public:
    Multi(Base *firstOperand = 0, Base *secondOperand = 0);
    double calculation();
};

class Fraction : public Base
{
public:
    Fraction(Base *firstOperand = 0, Base *secondOperand = 0);
    double calculation();
};

class Power : public Base
{
public:
    Power(Base *firstOperand = 0, Base *secondOperand = 0);
    double calculation();
};

class Variable : public Base
{
public:
    Variable(QString name);
    double calculation();

protected:
    QString varName;
};

class Number : public Base
{
public:
    Number(double num = 0);
    double calculation();

protected:
    double number;
};

class Func_OneParam : public Base
{
public:
    Func_OneParam(QString *name, Base *firstOperand = 0);
    double calculation();

protected:
    QString funcName;

private:
    double error(double param);
    std::pointer_to_unary_function<double,double> std_func;
    bool supported;
};

class Func_TwoParam : public Base
{
public:
    Func_TwoParam(QString *name, Base *firstOperand = 0, Base *secondOperand = 0);
    double calculation();

protected:
    QString funcName;

private:
    double error(double first, double second);
    std::pointer_to_binary_function<double,double,double> std_func;
    int funcCase;
};

#endif // BASE_H
