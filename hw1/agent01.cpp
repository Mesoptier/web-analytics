#include "agent01.h"
#include <sys/time.h>

agent01::agent01(int numberOfKeywords_, double monthBudget_){
	srand(time(NULL));
	numberOfKeywords = numberOfKeywords_;
	monthBudget = monthBudget_;
	budgetRemaining = monthBudget;

	// Initialize our variables
	currentMonth = 0;
	currentDayOfWeek = 0;
	currentDayOfMonth = 0;

	impressions.resize(7);
	averageImpressions.resize(7);
	for (int i = 0; i < 7; i++) {
		impressions[i].resize(numberOfKeywords);
		averageImpressions[i].resize(numberOfKeywords);
	}
}

agent01::~agent01(){
    //////////////////////////////////////////////////
    ///  Ensure that all created variables are properly de-allocated here
    //////////////////////////////////////////////////




    //////////////////////////////////////////////////
    //////////////////////////////////////////////////
}

void agent01::receiveInfo(int month, int day, int *imps_, int* clicks_, double* cost_, double* pos_){
	int clicksPerKeyword[numberOfKeywords];
	int impressionsPerKeyword[numberOfKeywords];
	double costPerKeyword[numberOfKeywords];
	double positionPerKeyword[numberOfKeywords];

	double totalCost = 0.0;
	for (int i = 0; i < numberOfKeywords; i++){
		impressionsPerKeyword[i] = imps_[i];
		clicksPerKeyword[i] = clicks_[i];
		costPerKeyword[i] = cost_[i];
		positionPerKeyword[i] = pos_[i];
		totalCost += cost_[i];
	}

	//////////////////////////////////////////////////
	///  Below here, make sure you store the info elsewhere and/or make your decisions here.
	///  Please ensure that when the month switches you get 1000 euro's extra budget
	//////////////////////////////////////////////////

	// If yesterday's month != today's month, increase the budget
	if (currentMonth != month) {
		currentMonth = month;
		currentDayOfMonth = 0;
		budgetRemaining += 1000;
	}

	currentDayOfWeek = day;
	currentDayOfMonth = currentDayOfMonth++;

	for (int i = 0; i < numberOfKeywords; i++){
		impressions[day][i].push_back(imps_[i]);

		// Calculate average number of impressions
		int total = 0;
		int size = impressions[day][i].size;

		for (int j = 0; j < size; j++) {
			total += impressions[day][i][j];
			size++;
		}

		averageImpressions[day][i] = total / (double)size;
	}

	//////////////////////////////////////////////////
	//////////////////////////////////////////////////
}

double* agent01::getBidsForAllKeywords(){
	double* allBids = new double[numberOfKeywords];     //Don't worry about garbage collection, is handled elsewhere!!!
	for (int i = 0; i < numberOfKeywords; i++)
		allBids[i] = getRandBetween0and1()*0.10;

	//////////////////////////////////////////////////
	///  Below here, make code to set the correct bids for the simulation
	//////////////////////////////////////////////////

    //first month we bid nothing for the keywords thus conserving money
    if (month == 0){
       for(int i=0;i<numberOfKeywords;i++)
            allBids[i]=0;
    } else {
        int totalImpressions = 0;
        for(int i=0;i<numberOfKeywords;i++)
            totalImpressions += impressions[3, i];

        double projectedClickFactor = totalbudget/totalImpressions;

        for(int i=0;i<numberOfKeywords;i++)
            allBids[i] = projectedClickFactor*

    }

	//////////////////////////////////////////////////
	//////////////////////////////////////////////////

	return allBids;
}

double* agent01::getMaxBudgetForAllKeywords(){
	double* allBudget = new double[numberOfKeywords];   //Garbage collection handled elsewhere
	for (int i = 0; i < numberOfKeywords; i++)
		allBudget[i] = 1000.0 / (numberOfKeywords * 30);

	//////////////////////////////////////////////////
	///  Below here, make code to set the correct budgets for the simulation
	//////////////////////////////////////////////////
	if (prevMonth == 0){

	}
	else {
		for (int i = 0; i < numberOfKeywords; i++)
		{	//moneyPerImpression moet nog aangemaakt worden
			allBudget[i] = averageImpressions[currentDayOfWeek][i]*moneyPerImpression;
		}
	}



	//////////////////////////////////////////////////
	//////////////////////////////////////////////////

	return allBudget;
}
