#include "GameBoard.h"

using namespace std;

Location::Location() :
        x(0), y(0) { }

Location::Location(int x, int y) :
        x(x), y(y) { }

Location::Location(const Location &otherLocation) :
        x(otherLocation.getX()), y(otherLocation.getY()) { }

int Location::getX() const {
    return this->x;
}

int Location::getY() const {
    return this->y;
}

void Location::setX(int newX) {
    this->x = newX;
}

void Location::setY(int newY) {
    this->y = newY;
}

bool Location::operator==(const Location &otherLocation) const {
    return (this->getX() == otherLocation.getX()) && (this->getY() == otherLocation.getY());
}

bool operator<(const Location &location1, const Location &location2) {
    return location1.getX() == location2.getX() ?
           location1.getY() < location2.getY() :
           location1.getX() < location2.getX();
}


GameBoard::GameBoard(Location goalLocation) {
    this->goalLocation = goalLocation;
}

GameBoard::GameBoard() {
    this->goalLocation = Location(5,5);
}

GameBoard::~GameBoard() {
}

GameBoard::GameBoard(const GameBoard& otherBoard) : treasureLocations(otherBoard.treasureLocations),
    enemyLocations(otherBoard.enemyLocations),
    goalLocation(otherBoard.goalLocation){}


bool GameBoard::isTreasure(Location location) const {
    return treasureLocations.find(location) != treasureLocations.end();
}

bool GameBoard::isEnemy(Location location) const {
    return enemyLocations.find(location) != enemyLocations.end();
}

Location GameBoard::getGoalLocation() const {
    return goalLocation;
}


void GameBoard::addEnemy(Location location) {
    enemyLocations.insert(location);
}

void GameBoard::killEnemy(Location location) {
    enemyLocations.erase(location);
}

void GameBoard::addTreasure(Location location) {
    treasureLocations.insert(location);
}

void GameBoard::removeTreasure(Location location) {
    treasureLocations.erase(location);
}
