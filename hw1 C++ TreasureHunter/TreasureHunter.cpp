#include "TreasureHunter.h"

TreasureHunter::TreasureHunter(int x, int y, GameBoard& board){
    location =  Location(x,y);
    oldLocation = Location(x,y);
    score = 50;
    this->board = &board;
    
    templocation = this->board->getGoalLocation();
    
}
TreasureHunter::~TreasureHunter(){
    /*delete this->location;
    delete this->board;
    delete this->oldLocation;
    delete this->templocation;*/

}

void TreasureHunter::changeBoard(GameBoard& newBoard){
    // TODo
    board = &newBoard;
    templocation = this->board->getGoalLocation();
}
void TreasureHunter::changeBoard(GameBoard* newBoard){
    // TODO
    board = newBoard;
    templocation = this->board->getGoalLocation();
}
int TreasureHunter::computeScore(std::string inputString){ 

    for(int i =0; i<inputString.length(); i++){
        if(board->isEnemy(location)){
            cout << endl << "Enemey Found" << endl;
            if(containsKonamiCode(inputString)){
                cout<< endl << "Konoami Code invincible!" << endl;
                board->killEnemy(location);
                cout << endl << "Enemy removed" << endl; 
            }
            else if(inputString.at(i) == 'a'){
            cout << endl << "Enemy removed" << endl; 
            board->killEnemy(location);
            }
            else if(inputString.at(i) == 'u' || inputString.at(i) == 'd' || inputString.at(i) == 'l' || inputString.at(i) == 'r' || inputString.at(i) == 'b'){
                cout << endl << "wrong input press a to attack!!" << endl ;
            }
            else{
                score--;
                cout << endl <<"wrong input!" << endl;
            }
            ;
        }   
        else if(inputString.at(i) == 'u'){

            oldLocation = Location(location);
            location.setY(location.getY()+1);
            if(containsKonamiCode(inputString)){
                board->killEnemy(location);
            }
            cout << endl << "Treasure Hunter x.y is:" << location.getX() << "," <<location.getY() <<endl;
            if(Location(templocation) == Location(location)){
            score += 101;
            cout << endl <<"You Win!" << endl;
            break;
            }
            if(board->isTreasure(location)){
                cout << endl <<"Treasure Found" << endl;
                score += 10;
                board->removeTreasure(location); 
                cout << endl << "Treasure Removed" << endl; 
            }           
           /* cout << endl << oldLocation->getX() << endl;
            cout << endl << templocation->getX() << endl;
            cout << endl << std::abs (location->getX()-templocation->getX()) << endl;
            cout << endl << std::abs (oldLocation->getX()-templocation->getX()) << endl;*/
           
            if( std::abs (location.getY() - templocation.getY()) <  std::abs (oldLocation.getY() - templocation.getY())){
                score += 1;
                cout << endl << "score increased!" << endl;
                cout << endl << score << endl;
            }
            
            else{
                score -= 2;
                cout << endl << "score decreased!" << endl;
                cout << endl << score << endl;
                if(score == 0 || score < 0){
                cout<< "You lose!" <<endl;   
                break; 
                }
            } 
        }
        else if(inputString.at(i) == 'd'){
            oldLocation = Location(location);
            location.setY(location.getY()-1);
            if(containsKonamiCode(inputString)){
                board->killEnemy(location);
            }
            cout << endl << "Treasure Hunter x.y is:" << location.getX() << "," << location.getY() <<endl;
            if(Location(templocation) == Location(location)){
            score += 101;
            cout << endl <<"You Win!" << endl;
            break;
            }
            if(board->isTreasure(location)){
                cout << endl <<"Treasure Found" << endl;
                score += 10;
                board->removeTreasure(location); 
                cout << endl << "Treasure Removed" << endl; 

            }  
            if( std::abs (location.getY() - templocation.getY()) <  std::abs (oldLocation.getY() - templocation.getY())){
                score += 1;
                cout << endl << "score increased!" << endl;
                cout << endl << score << endl;
            }
            else{
                score-=2; 
                cout << endl << "score decreased!" << endl;
                cout << endl << score << endl;
                if(score == 0 || score < 0){
                cout<< "You lose!" <<endl;   
                break; 
                }
            }
        }
        else if(inputString.at(i) == 'l'){
            oldLocation = Location(location);
            cout << endl << "goal: " << templocation.getX() << endl;
            location.setX(location.getX()-1);
            if(containsKonamiCode(inputString)){
                board->killEnemy(location);
            }
            cout << endl << "Treasure Hunter x.y is:" << location.getX() << "," <<location.getY() <<endl;
            if(Location(templocation) == Location(location)){
            score += 101;
            cout << endl <<"You Win!" << endl;
            break;
            }
            if(board->isTreasure(location)){
                cout << endl <<"Treasure Found" << endl;
                score += 10;
                board->removeTreasure(location); 
                cout << endl << "Treasure Removed" << endl; 
            }  
            if(std::abs (location.getX() - templocation.getX()) <  std::abs (oldLocation.getX() - templocation.getX())){
                score += 1;
                cout << endl << "score increased!" << endl;
                cout << endl << score << endl;
            }
            else{
                score -= 2;
                cout << endl << "score decreased!" << endl;
                cout << endl << score << endl;
                if(score == 0 || score < 0){
                cout<< "You lose!" <<endl;   
                break; 
                }
            }
        }
        else if(inputString.at(i) == 'r'){
            oldLocation = Location(location);
            location.setX(location.getX()+1);
            if(containsKonamiCode(inputString)){
                board->killEnemy(location);
            }
            cout << endl << "Treasure Hunter x.y is:" << location.getX() << "," << location.getY() <<endl;
            
            if(Location(templocation) == Location(location)){
            score += 101;
            cout << endl <<"You Win!" << endl;
            break;
            }
            if(board->isTreasure(location)){
                cout << endl <<"Treasure Found" << endl;
                score += 10;
                board->removeTreasure(location); 
                cout << endl << "Treasure Removed" << endl; 
            }  
            if(std::abs (location.getX() - templocation.getX()) <  std::abs (oldLocation.getX() - templocation.getX())){
                score+= 1;
                cout << endl << "score increased!" << endl;
                cout << endl<< score << endl;
            }
            else{
                score -=2;
                cout << endl << "Score decreased!" << endl;
                cout << endl << score << endl;
                if(score == 0 || score < 0){
                cout<< "You lose!" <<endl;   
                break; 
                }
            }
            
        }
        else if(inputString.at(i)=='b'){
            
        }
        else if(inputString.at(i) == 'a'){
            
        }
        else{
            score --;
            cout << endl << "wrong input!!" << endl;
            if(score == 0 || score < 0){
            cout<< "You lose!" <<endl;   
            break; 
            }   
        }
        if(score == 0 || score < 0){
            return 0;
            break; 
        }
        



}
return score;
}

