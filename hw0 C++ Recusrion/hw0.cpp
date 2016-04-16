#include <string>
#include <iostream>
using namespace std; 

int countCharOnEven(std::string phrase, char letter){
    int a = 0;
    for(int i = 0; i<phrase.length(); i++){
        if(phrase.at(i) == letter && i%2 == 0){
        	a++;
        }
    }
    
    return a;
}


int computeFibonacci(int number){
     int oldfib = 0;
    int newfib = 1;
    int fib = 0;
    for(int i =1; i<number; i++){
    fib = oldfib + newfib;
    oldfib = newfib; 
    newfib = fib;

    }
    if (number == 1){
        fib = 1;
    }
    return fib;
}

int main() {
  cout << computeFibonacci(4) << endl;
  


  return 0;


}
