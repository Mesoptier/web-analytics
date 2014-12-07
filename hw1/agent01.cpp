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
	budgetRemaining = 0;
	firstWeek = 10;
	impressions.resize(7);
	averageImpressions.resize(7);
	position.resize(7);
	cost.resize(7);
	multiplier.resize(7);
	for (int i = 0; i < 7; i++) {
		impressions[i].resize(numberOfKeywords);
		averageImpressions[i].resize(numberOfKeywords);
		position[i].resize(numberOfKeywords);
		cost[i].resize(numberOfKeywords);
		multiplier[i].resize(numberOfKeywords);
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

	//collect data
	budgetRemaining -= totalCost;
	currentDayOfWeek = day + 1;
	for (int i = 0; i < numberOfKeywords; i++){
		impressions[day][i].push_back(imps_[i]);
		position[day][i] = pos_[i];
		cost[day][i] = cost_[i];
	}

	// If yesterday's month != today's month, increase the budget and do calculations
	if (currentMonth != month) {
		currentMonth = month;
		if (currentMonth == 1){
			firstWeek = 0;
		}
		budgetRemaining += 1333;
		//add yesterdays impressions
		for (int i = 0; i < numberOfKeywords; i++){
			impressions[day][i].push_back(imps_[i]);
		}
		//calculate the average number of impressions
		//for each day
		for (int i = 0; i < 6; i++)
		{	// for each keyword
			for (int j = 0; j < numberOfKeywords; j++)
			{
				//variable to hold the total
				int total = 0;
				//number of values for each keyword for each day
				int size = impressions[(day + i) % 7][j].size();
				//add each value to the total
				for (int k = 0; k < size; k++) {
					total += impressions[(day + i) % 7][j][k];
				}
				//divide the total by the number of values
				if (size == 0){
					//little bit of exception handling without really handling it
					//it shouldn't be possible to get here.
					//this is for compilation reasons
				}
				else {
					averageImpressions[(day + i) % 7][j] = (double)(total / size);
				}
			}
		}
		//get the expected number of impressions for this month
		impressionsThisMonth = 0;
		for (int i = 0; i < numberOfKeywords; i++){
			//since a month is defined to have 30 days, the first 2 days occur 5 times
			for (size_t j = 1; j < 3; j++)
			{
				impressionsThisMonth += 5 * averageImpressions[(day + j) % 7][i];
			}
			for (size_t j = 3; j < 8; j++)
			{
				impressionsThisMonth += 4 * averageImpressions[(day + j) % 7][i];
			}
		}
		//divide the money equally over the expected impressions
		if (impressionsThisMonth == 0){
			//little bit of exception handling without really handling it
			//it shouldn't be possible to get here
			//this is for compilation reasons
		}
		else {
			moneyPerImpression = budgetRemaining / impressionsThisMonth;
		}
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
	if (currentMonth == 0){
		for (int i = 0; i<numberOfKeywords; i++)
			allBids[i] = 0;
	}
	else {
		if (firstWeek<7){
			firstWeek++;
			for (int i = 0; i < numberOfKeywords; i++){
				multiplier[currentDayOfWeek][i] = 10;
				allBids[i] = multiplier[currentDayOfWeek][i] * moneyPerImpression;
			}
		}
		else {
			for (int i = 0; i < numberOfKeywords; i++){
				//if half of the budget is not used
				if (cost[currentDayOfWeek][i]<2 * averageImpressions[currentDayOfWeek][i] * moneyPerImpression
					&&position[currentDayOfWeek][i]>1){
					//increase the multiplier
					multiplier[currentDayOfWeek][i] *= 2;
				}
				else
					//if the full budget is not used
				if (cost[currentDayOfWeek][i]<averageImpressions[currentDayOfWeek][i] * moneyPerImpression
					&&position[currentDayOfWeek][i]>1){
					//increase the multiplier
					multiplier[currentDayOfWeek][i]++;
				}
				else
					//if the full budget is used
				if (cost[currentDayOfWeek][i] >= averageImpressions[currentDayOfWeek][i] * moneyPerImpression){
					//decrease the multiplier
					if (multiplier[currentDayOfWeek][i] > 1){
						multiplier[currentDayOfWeek][i]--;
					}
				}
				//set the bids
				allBids[i] = multiplier[currentDayOfWeek][i] * moneyPerImpression;
			}
		}
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
	if (currentMonth == 0){
		for (int i = 0; i < numberOfKeywords; i++)
		{
			allBudget[i] = 0;
		}
	}
	else {
		for (int i = 0; i < numberOfKeywords; i++)
		{
			allBudget[i] = averageImpressions[currentDayOfWeek][i] * moneyPerImpression;
		}
	}

	//////////////////////////////////////////////////
	//////////////////////////////////////////////////

	return allBudget;
}