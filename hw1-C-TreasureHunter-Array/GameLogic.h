#ifndef UNTITLED_GAMELOGIC_H
#define UNTITLED_GAMELOGIC_H

#include <iostream>

class GameLogic {

public:
    bool containsKonamiCode(std::string inputString);
    virtual int computeScore(std::string inputString) =0;
};


#endif //UNTITLED_GAMELOGIC_H
