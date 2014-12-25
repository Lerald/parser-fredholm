#ifndef COREFUNC_H
#define COREFUNC_H

#include <QMap>
#include <QString>

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
