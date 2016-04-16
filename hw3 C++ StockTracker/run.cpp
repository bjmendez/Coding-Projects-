#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include "StockTracker.h"

using namespace std;

void sampleUsage();
void realDataUsage();

int main() {
    sampleUsage();
    realDataUsage();
    return 0;
}

void sampleUsage() {

    // This is what we typically put in a run.cpp. It is by no means comprehensive testing. It is just enough to give a
    // a sample of how each function is called.
    //
    // Please note the significant difference between this and test cases!
    //

    StockTracker tracker;

    tracker.registerTicker("StockA", 100);
    tracker.registerTicker("StockB", 200);
    tracker.registerTicker("StockC", 300);
    tracker.registerTicker("StockD", 200);

    tracker.isTicker("StockA"); // return true
    tracker.isTicker("StockB"); // return true
    tracker.isTicker("StockC"); // return true

    tracker.isTicker("StockE"); // return false
    tracker.isTicker("stockC"); // return false
    tracker.isTicker("Stocka"); // return false
    tracker.isTicker("GOOG"); // return false

    tracker.getSharesOutstanding("StockA"); // return 100
    tracker.getSharesOutstanding("StockB"); // return 200
    tracker.getSharesOutstanding("StockC"); // return 300
    tracker.getSharesOutstanding("StockD"); // return 200
    tracker.getSharesOutstanding("StockE"); // return 0

    tracker.updateCurrentPrice("StockA", 10.0);
    tracker.updateCurrentPrice("StockA", 10.2);
    tracker.updateCurrentPrice("StockA", 10.3);
    tracker.getCurrentPrice("StockA"); // return 10.3
    tracker.updateCurrentPrice("StockA", 11.6);
    tracker.getCurrentPrice("StockA"); // return 11.6
    tracker.updateCurrentPrice("StockB", 5.25);
    tracker.getCurrentPrice("StockB"); // return 5.25
    tracker.getCurrentPrice("StockC"); // return 0.0

    tracker.getMarketCap("StockA"); // return 1160.0
    tracker.getMarketCap("StockB"); // return 1050.0
    tracker.getMarketCap("StockC"); // return 0.0
    tracker.getMarketCap("StockD"); // return 0.0
    tracker.getMarketCap("StockE"); // return 0.0

    tracker.topMarketCaps(1); // return vector with vector.at(0) == "StockA"
    tracker.topMarketCaps(2); // return vector with vector.at(0) == "StockA" and vector.at(1) == "StockB"


    // To get the 3rd point, your code must be able to handle ties in market cap
    // register IPO1 100
    // register IPO2 200
    // register IPO3 500
    // set price IPO1 20.0
    // set price IPO2 10.0
    // set price IPO3 2.0

    // top 2 must return IPO1 and IPO2. The order doesn't matter since they are tied

}


void realDataUsage(){

    srand(time(NULL));

    StockTracker stockTracker;

    string totalSharesFilename = "sharesOutstanding.csv";
    string pricesFilename = "2016May3Price.csv";

    ifstream shares;
    ifstream currentPrices;

    shares.open(totalSharesFilename);
    currentPrices.open(pricesFilename);

    // Always check to see if file opening succeeded
    if (!shares.is_open())
    {
        cout << "Could not open " + totalSharesFilename + "\n";
        return;
    }
    if (!currentPrices.is_open())
    {
        cout << "Could not open " + pricesFilename + "\n";
        return;
    }


    string lineFromFile;
    getline(shares, lineFromFile); // Strip reference

    // Assumes specific format is followed
    while(getline(shares, lineFromFile)){
        string ticker = lineFromFile.substr(0,lineFromFile.find(","));
        // Market cap in thousands of shares
        int totalShares = stoi(lineFromFile.substr(lineFromFile.find(",")+1, lineFromFile.length() - lineFromFile.find(",") - 4));
        stockTracker.registerTicker(ticker, totalShares);
    }


    getline(currentPrices, lineFromFile); // Strip reference

    vector<pair<string,double> > stockPrices;

    // Assumes specific format is followed
    while(getline(currentPrices, lineFromFile)){
        string ticker = lineFromFile.substr(0,lineFromFile.find(","));
        double stockPrice = stod(lineFromFile.substr(lineFromFile.find(",")+1));
        stockPrices.push_back(make_pair(ticker,stockPrice));
    }


    vector<pair<string,double> >::iterator itPair;

    clock_t startTime = clock();

    for(itPair = stockPrices.begin(); itPair != stockPrices.end(); itPair++){
        string ticker = (*itPair).first;
        double stockPrice = (*itPair).second;
        for(int i=0; i<10; i++) {
            stockTracker.updateCurrentPrice(ticker, 100.0 * ((double) rand() / RAND_MAX)); // Simulate a changing price
        }
        stockTracker.updateCurrentPrice(ticker, stockPrice); // Replace random value with actual price
    }


    vector <string> topStocks;
    int topK = 20;
    // Run multiple times for timing test
    for(int i=0; i<5; i++) {
        topStocks = stockTracker.topMarketCaps(topK);
    }

    double elapsedTime = (double(clock() - startTime) / CLOCKS_PER_SEC)*1000.0;

    int rank = 1;
    for(vector<string>::iterator it = topStocks.begin(); it != topStocks.end(); it ++){
        string currentTicker = *it;
        cout << rank << ": " << currentTicker <<
        " | market cap: " << stockTracker.getMarketCap(currentTicker) <<
        " | price: " << stockTracker.getCurrentPrice(currentTicker) <<
        " | share outstanding: " << stockTracker.getSharesOutstanding(currentTicker) << endl;
        rank++;
    }

    cout << "\nElapsed time: " << elapsedTime << "ms" << endl;

//    1: AAPL | market cap: 5.62886e+08 | price: 101.52 | share outstanding: 5544583
//    2: GOOG | market cap: 4.89567e+08 | price: 711.25 | share outstanding: 688319
//    3: MSFT | market cap: 4.13914e+08 | price: 52.3325 | share outstanding: 7909302
//    4: XOM | market cap: 3.41896e+08 | price: 82.33 | share outstanding: 4152756
//    5: FB | market cap: 3.11411e+08 | price: 109.41 | share outstanding: 2846280
//    6: GE | market cap: 2.94703e+08 | price: 30.2415 | share outstanding: 9745000
//    7: JNJ | market cap: 2.94368e+08 | price: 106.68 | share outstanding: 2759359
//    8: AMZN | market cap: 2.71728e+08 | price: 577.11 | share outstanding: 470842
//    9: WFC | market cap: 2.52135e+08 | price: 49.665 | share outstanding: 5076712
//    10: T | market cap: 2.33684e+08 | price: 37.99 | share outstanding: 6151208
//    11: PG | market cap: 2.24181e+08 | price: 82.89 | share outstanding: 2704565
//    12: JPM | market cap: 2.18993e+08 | price: 59.785 | share outstanding: 3663001
//    13: VZ | market cap: 2.11453e+08 | price: 51.905 | share outstanding: 4073841
//    14: WMT | market cap: 2.10531e+08 | price: 66.08 | share outstanding: 3186000
//    15: KO | market cap: 1.90065e+08 | price: 43.9 | share outstanding: 4329497
//    16: PFE | market cap: 1.8448e+08 | price: 29.885 | share outstanding: 6173001
//    17: V | market cap: 1.76964e+08 | price: 73.715 | share outstanding: 2400645
//    18: CVX | market cap: 1.64748e+08 | price: 87.485 | share outstanding: 1883156
//    19: DIS | market cap: 1.6106e+08 | price: 98.715 | share outstanding: 1631570
//    20: ORCL | market cap: 1.59016e+08 | price: 37.85 | share outstanding: 4201220
//
//    Elapsed time: 30ms

}