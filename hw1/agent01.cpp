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
	historicBidPrices.resize(7);
	historicCostPaid.resize(7);
	historicPositions.resize(7);
	for (int i = 0; i < 7; i++) {
		impressions[i].resize(numberOfKeywords);
		averageImpressions[i].resize(numberOfKeywords);
		historicBidPrices[i].resize(numberOfKeywords);
		historicCostPaid[i].resize(numberOfKeywords);
		historicPositions[i].resize(numberOfKeywords);
	}
}

agent01::~agent01(){
    //////////////////////////////////////////////////
    ///  Ensure that all created variables are properly de-allocated here
    //////////////////////////////////////////////////




    //////////////////////////////////////////////////
    //////////////////////////////////////////////////
}

void agent01::receiveInfo(int month, int day, int* imps_, int* clicks_, double* cost_, double* pos_){
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
	currentDayOfMonth++;

	for (int i = 0; i < numberOfKeywords; i++){
		impressions[day][i].push_back(imps_[i]);

		// Calculate average number of impressions
		int total = 0;
		int size = impressions[day][i].size();

		for (int j = 0; j < size; j++) {
			total += impressions[day][i][j];
		}

		averageImpressions[day][i] = total / (double)size;

		historicCostPaid[day][i] = cost[i];
		historicPositions[day][i] = pos[i];
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

    int currentDay;

    //first month we bid nothing for the keywords thus conserving money
    if (currentMonth == 0){
       for(int i=0;i<numberOfKeywords;i++)
            allBids[i]=0;
    } else {
        int totalImpressions = 0;
        for(int i=0;i<numberOfKeywords;i++){
            //figure out the day for which we calculate bids
            if (currentDayOfWeek == 6){
                currentDay = 0;
            } else {
                currentDay = currentDayOfWeek+1;
            }
            //total number of impressions across all keywords
            totalImpressions += averageImpressions[currentDay][i];

        }
        //calculate  proportional factor of money per impression
        moneyPerImpression = monthBudget/totalImpressions;

        //TODO use moneyPerImpression proportional mltiplier to figure out
        //a reasonabe amount to bid
        //also base this chocie on previous bid positiions.
        for(int i=0;i<numberOfKeywords;i++)
            allBids[i] = moneyPerImpression*averageImpressions[currentDay][i];

    }

    for(int i=0;i<numberOfKeywords;i++)
        historicBids[currentDay] = allBids[i];

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
	if (currentMonth == 0){

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
