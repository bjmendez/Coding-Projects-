#include <string>
#include "GameLogic.h"

/*
 *Returns whether or not the Konami Code was contained in the input
 */
bool GameLogic::containsKonamiCode(std::string inputFile){
	std::size_t found = inputFile.find("uuddlrlrba");
    if(found!=std::string::npos){
    	return true;
    }
    else{
    	return false;
    }
    
}
