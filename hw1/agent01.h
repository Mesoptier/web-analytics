#ifndef AGENT01_H
#define AGENT01_H

#include <QtCore>

class agent01{
public:
<<<<<<< Updated upstream
	agent01(int numberOfKeywords_, double monthBudget_);
	~agent01();
	void receiveInfo(int month, int day, int* imps_, int* clicks_, double* cost_, double* pos_);
	double* getBidsForAllKeywords();
	double* getMaxBudgetForAllKeywords();
=======
    agent01(int numberOfKeywords_,double monthBudget_);
    ~agent01();
    void receiveInfo(int month, int day, int* imps_, int* clicks_, double* cost_, double* pos_);
    double* getBidsForAllKeywords();
    double* getMaxBudgetForAllKeywords();
>>>>>>> Stashed changes

private:
	int numberOfKeywords;
	double getRandBetween0and1(){ return ((double)rand()) / RAND_MAX; }
	double monthBudget;
	double budgetRemaining;

<<<<<<< Updated upstream
	int prevMonth;
	vector< vector< vector<int> > > impressions;
=======
    int prevMonth;
    int prevDayOfMonth;
>>>>>>> Stashed changes
};

#endif // AGENT01_H
