#ifndef AGENT01_H
#define AGENT01_H

#include <QtCore>

class agent01{
public:
    agent01(int numberOfKeywords_,double monthBudget_);
    ~agent01();
    void receiveInfo(int month, int day, int* clicks_, double* cost_, double* pos_);
    double* getBidsForAllKeywords();
    double* getMaxBudgetForAllKeywords();

private:
    int numberOfKeywords;
    double getRandBetween0and1(){return ((double)rand())/RAND_MAX;}
    double monthBudget;
    double budgetRemaining;

    int prevMonth;
};

#endif // AGENT01_H
