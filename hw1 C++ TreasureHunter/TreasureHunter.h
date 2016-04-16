#ifndef UNTITLED_TREASUREHUNTER_H
#define UNTITLED_TREASUREHUNTER_H

#include "GameBoard.h"
#include <cmath>
//add instance variables
class TreasureHunter : public GameLogic  {
    private:
    	GameBoard *board;
    	Location location;
        Location  oldLocation;
        Location templocation;
        int score; 
    public:

        //The Params are the starting locations of the Hunter, x and y respectively
        TreasureHunter(int, int, GameBoard&);
        ~TreasureHunter();

        void changeBoard(GameBoard&);
        void changeBoard(GameBoard*);//ASSIGN NEW BOARD

        virtual int computeScore(std::string inputString);
};

#endif //UNTITLED_TREASUREHUNTER_H
