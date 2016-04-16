#ifndef UNTITLED_GAMEBOARD_H
#define UNTITLED_GAMEBOARD_H

#include <set>
#include <unordered_map>
#include <utility>
#include <sstream>
#include "GameLogic.h"

using namespace std;

// Wrapper class for an (x,y) point
class Location{
private:
    int x;
    int y;

public:
    Location();
    Location(int, int);
    Location(const Location&);
    void setX(int);
    void setY(int);
    int getX() const;
    int getY() const;
    bool operator==(const Location& otherLocation) const;
};


bool operator<(const Location& location1, const Location& location2);


class GameBoard {
private:
    Location goalLocation;
    set<Location> treasureLocations;
    set<Location> enemyLocations;

public:
    GameBoard(Location goalLocation);
    GameBoard();
    ~GameBoard();
    GameBoard(const GameBoard&);

    void addEnemy(Location);
    void addTreasure(Location);


    // You only need to call these GameBoard functions for the assignment
    bool isTreasure(Location) const;
    bool isEnemy(Location) const;
    Location getGoalLocation() const;
    void killEnemy(Location);
    void removeTreasure(Location);
};


#endif //UNTITLED_GAMEBOARD_H
