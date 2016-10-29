#include "TreasureHunter.h"


// initializing instance variables
TreasureHunter::TreasureHunter(int x, int y, GameBoard& board){
    location =  Location(x,y);
    oldLocation = Location(x,y);
    score = 50;
    this->board = &board;
    
    templocation = this->board->getGoalLocation();
    
}

//Method for changing the gameboard by reference

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
//Method to compute the score of treasure Hnter
int TreasureHunter::computeScore(std::string inputString){ 
    //Iterate input string of treasure Hunter moves
    for(int i =0; i<inputString.length(); i++){
        //If treasure hunter moves on top enemy 
        if(board->isEnemy(location)){
            cout << endl << "Enemey Found" << endl;
            //If treasure Hunter is invincible 
            if(containsKonamiCode(inputString)){
                cout<< endl << "Konoami Code invincible!" << endl;
                board->killEnemy(location);
                cout << endl << "Enemy removed" << endl; 
            }
            //If treasue Hunter presses 'a' the attack button, the enemy is removd
            else if(inputString.at(i) == 'a'){
            cout << endl << "Enemy removed" << endl; 
            board->killEnemy(location);
            }
            //If not attacking tell player to attack
            else if(inputString.at(i) == 'u' || inputString.at(i) == 'd' || inputString.at(i) == 'l' || inputString.at(i) == 'r' || inputString.at(i) == 'b'){
                cout << endl << "wrong input press a to attack!!" << endl ;
            }
            //If invalid command is put in subtract from score
            else{
                score--;
                cout << endl <<"wrong input!" << endl;
            }
            ;
        }   
        //If the treasure hunter moves up
        else if(inputString.at(i) == 'u'){

            oldLocation = Location(location);
            location.setY(location.getY()+1);
            //If enenmy is found and invincible kill it
            if(containsKonamiCode(inputString)){
                board->killEnemy(location);
            }
            cout << endl << "Treasure Hunter x.y is:" << location.getX() << "," <<location.getY() <<endl;
            //If treasure hunter has found the goal add 101 points to score and end his hunt
            if(Location(templocation) == Location(location)){
            score += 101;
            cout << endl <<"You Win!" << endl;
            break;
            }
            //If treasue Hunter finds a treasure add 10 points to his score
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
            // If Treasure Hunter moves closer to treasure Increase his score by 1
            if( std::abs (location.getY() - templocation.getY()) <  std::abs (oldLocation.getY() - templocation.getY())){
                score += 1;
                cout << endl << "score increased!" << endl;
                cout << endl << score << endl;
            }
            // Else if Treasure Hunter moves further away subtract 2
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
        //when moving down
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
        //when moving left
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
        // When moving right 
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
            //purpose is for konoami code 
        }
        else if(inputString.at(i) == 'a'){
            //Purpose is for attacking does not effect score 
        }
        // An invalid input and points are taken away 
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

