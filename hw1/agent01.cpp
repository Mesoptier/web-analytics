#include "agent01.h"
#include <sys/time.h>

agent01::agent01(int numberOfKeywords_, double monthBudget_){
    srand(time(NULL));
    numberOfKeywords=numberOfKeywords_;
    monthBudget=monthBudget_;
    budgetRemaining=monthBudget;
}

agent01::~agent01(){
    //////////////////////////////////////////////////
    ///  Ensure that all created variables are properly de-allocated here
    //////////////////////////////////////////////////
	//test


	
    //////////////////////////////////////////////////
    //////////////////////////////////////////////////
}

void agent01::receiveInfo(int month, int day, int *imps_, int* clicks_, double* cost_, double* pos_){
    int clicksPerKeyword[numberOfKeywords];
    int impressionsPerKeyword[numberOfKeywords];
    double costPerKeyword[numberOfKeywords];
    double positionPerKeyword[numberOfKeywords];

    double totalCost=0.0;
    for(int i=0;i<numberOfKeywords;i++){
        impressionsPerKeyword[i]=imps_[i];
        clicksPerKeyword[i]=clicks_[i];
        costPerKeyword[i]=cost_[i];
        positionPerKeyword[i]=pos_[i];
        totalCost+=cost_[i];
    }

    //////////////////////////////////////////////////
    ///  Below here, make sure you store the info elsewhere and/or make your decisions here.
    ///  Please ensure that when the month switches you get 1000 euro's extra budget
    //////////////////////////////////////////////////




    //////////////////////////////////////////////////
    //////////////////////////////////////////////////
}

double* agent01::getBidsForAllKeywords(){
    double* allBids = new double[numberOfKeywords];     //Don't worry about garbage collection, is handled elsewhere!!!
    for(int i=0;i<numberOfKeywords;i++)
        allBids[i]=getRandBetween0and1()*0.10;

    //////////////////////////////////////////////////
    ///  Below here, make code to set the correct bids for the simulation
    //////////////////////////////////////////////////




    //////////////////////////////////////////////////
    //////////////////////////////////////////////////

    return allBids;
}

double* agent01::getMaxBudgetForAllKeywords(){
    double* allBudget = new double[numberOfKeywords];   //Garbage collection handled elsewhere
    for(int i=0;i<numberOfKeywords;i++)
        allBudget[i]=1000.0/(numberOfKeywords*30);

    //////////////////////////////////////////////////
    ///  Below here, make code to set the correct budgets for the simulation
    //////////////////////////////////////////////////




    //////////////////////////////////////////////////
    //////////////////////////////////////////////////

    return allBudget;
}
