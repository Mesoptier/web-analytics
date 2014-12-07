#ifndef AGENT01_H
#define AGENT01_H

#include<vector>
#include <cstdlib>

using namespace std;

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
	double impressionsThisMonth;
	double moneyPerImpression;
	int firstWeek;
	vector< vector< vector<int> > > impressions;	//impressions[day][keyword][i]
	vector< vector<double> > averageImpressions;	//avg impressions[day][keyword]
	vector< vector<int> > position;					//position[day][keyword]
	vector< vector<int> > multiplier;				//multiplier[day][keyword]
	vector< vector<double> > cost;					//cost[day][keyword]
};

#endif // AGENT01_H
