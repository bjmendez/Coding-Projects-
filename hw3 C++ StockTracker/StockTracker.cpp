#include "StockTracker.h"

StockTracker::StockTracker(){}


void StockTracker::registerTicker(string tickerSymbol, int sharesOutstanding){
    stock.insert ( pair<string,int>(tickerSymbol,sharesOutstanding) );
}

bool StockTracker::isTicker(string tickerSymbol){
	if(stock.count(tickerSymbol) == 1){
		return true;
	}
	else{
		return false;
	}
}

int StockTracker::getSharesOutstanding(string tickerSymbol){
	if(stock.count(tickerSymbol) == 0){
		return 0;
	}
    else{
		return stock[tickerSymbol];
	}
}




void StockTracker::updateCurrentPrice(string tickerSymbol, double price){
    
    if(stockprice.count(tickerSymbol) == 1){
        double marketcap = stockprice[tickerSymbol] * stock[tickerSymbol];
        stockprice.erase (tickerSymbol);
        stockprice.insert ( pair<string,double>(tickerSymbol,price) );
        stocks.erase(marketcap);
        marketcap = stockprice[tickerSymbol] * stock[tickerSymbol];
        stocks.insert ( pair<double, string>(marketcap, tickerSymbol) );
    }
    else{
        stockprice.insert ( pair<string,double>(tickerSymbol,price) );
        double marketcap = stockprice[tickerSymbol] * stock[tickerSymbol]; 
        stocks.insert ( pair<double, string>(marketcap, tickerSymbol) );
    }
    
    
    
    

}

double StockTracker::getCurrentPrice(string tickerSymbol){
    if(stockprice.count(tickerSymbol) == 0){
    	return 0.0;
    }
    else{
    	return stockprice[tickerSymbol];
    }
}

double StockTracker::getMarketCap(string tickerSymbol){
    if(stockprice.count(tickerSymbol) == 0){
    	return 0.0;
    }
    else{
    	return stockprice[tickerSymbol] * stock[tickerSymbol];
    }
}


vector<string> StockTracker::topMarketCaps(int k){
	vector<string> top; 
    multimap<double, string,compareMarketCaps>::iterator it = stocks.begin();
   for(int i =0; i<k; i++, it++){
    	top.push_back(it->second);
        
}

return top;
}