#include "base.h"
#include "math.h"
#include "stdio.h"

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
    double t = head->getVariable(varName);
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
