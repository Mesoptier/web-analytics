#ifndef AGENT01_H
#define AGENT01_H

#include <cstdlib>
#include <vector>


class agent01{
public:
	agent01(int numberOfKeywords_, double monthBudget_);
	~agent01();
	void receiveInfo(int month, int day, int* imps_, int* clicks_, double* cost_, double* pos_);
	double* getBidsForAllKeywords();
	double* getMaxBudgetForAllKeywords();

private:
	int numberOfKeywords;
	double getRandBetween0and1(){ return ((double)rand()) / RAND_MAX; }
	double monthBudget;
	double budgetRemaining;

	int currentMonth;
	int currentDayOfWeek;
	int currentDayOfMonth;
	double moneyPerImpression;
	std::vector< std::vector< std::vector<int> > > impressions; // impressions[day][keyword][i]
	std::vector< std::vector<double> > averageImpressions; // impressions[day][keyword]
};

#endif // AGENT01_H
