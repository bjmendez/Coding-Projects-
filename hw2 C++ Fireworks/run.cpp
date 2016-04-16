#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <unordered_set>

#include "FireworkFactory.h"

using namespace std;

void sampleUsage();

bool testFactory(int numberOfShipments,
                 int sizeOfFireworkShipment,
                 int sizeOfMetalShipment,
                 int purchaseSize,
                 int numberOfPurchases,
                 bool sellByColor);

bool sample1();
bool sample2();
bool sample3();
bool sample4();


int main() {

    // use this line to get different results on each run
//    srand(time(NULL));

    sampleUsage();

    sample1();
    sample2();
    sample3();
    sample4();

    cout << "-end of main-" << endl;
    cout << (Firework::getTotalFireworks() - Firework::getHeapFireworks()) << " firework(s) remain on the stack" << endl;
    cout << Firework::getHeapFireworks() << " firework(s) remain on the heap" << endl;

    cout << "\n***NOTE*** These are not the same tests that will be used for grading. The output of these functions "
                    "does not reflect your actual grade. Please submit to recieve an official grade." << endl;

    return 0;
}



void sampleUsage() {

    // This is what we typically put in a run.cpp. It is by no means comprehensive testing. It is just enough to give a
    // a sample of how each function is called.
    //
    // Please note the significant difference between this and the test cases!
    //

    int sizeOfFireworkShipment = 20;
    int sizeOfMetalShipment = 30;

    FireworkFactory* factory = new FireworkFactory();

    stack < Firework * > fireworksToShip;

    for (int i = 0; i < sizeOfFireworkShipment; i++) {
        Firework *firework = new Firework(static_cast<Color>(rand() % 4));
        fireworksToShip.push(firework);
    }

    factory->fireworkShipment(fireworksToShip);


    stack <Metal> metal;

    for (int i = 0; i < sizeOfMetalShipment; i++) {
        metal.push(static_cast<Metal>(rand() % 4));
    }

    factory->metalShipment(metal);


    stack < Firework * > *customerFireworks = new stack<Firework *>();

    factory->sellFireworks(*customerFireworks, 4);
    factory->sellFireworks(*customerFireworks, 2, Blue);

    while (!customerFireworks->empty()) {
        delete customerFireworks->top();
        customerFireworks->pop();
    }

    delete customerFireworks;
    delete factory;
}



/*** Sample testing code below. These are not the official tests for grading ***/
/*** No need to read except for curiosity and to further your understanding  ***/

bool testFactory(int numberOfShipments,
                 int sizeOfFireworkShipment,
                 int sizeOfMetalShipment,
                 int purchaseSize,
                 int numberOfPurchases,
                 bool sellByColor){

    FireworkFactory* factory = new FireworkFactory();

    stack < Firework * > fireworksToShip;
    queue <Color> colorOrder;
    stack <Metal> metal;
    stack <Color> colorOrderPurchase;
    int metals[4] = {0};
    int purchaseByColor[4] = {0};

    for (int j = 0; j < numberOfShipments; j++) {

        // Firework Shipments
        stack<Color> tempStack;
        for (int i = 0; i < sizeOfFireworkShipment; i++) {
            Firework *firework = new Firework(static_cast<Color>(rand() % 4));
            tempStack.push(firework->getColor());
            fireworksToShip.push(firework);
        }
        while(!tempStack.empty()){
            colorOrder.push(tempStack.top());
            tempStack.pop();
        }
        factory->fireworkShipment(fireworksToShip);


        // Metal Shipments
        stack<Metal> tempMetal;
        for (int i = 0; i < sizeOfMetalShipment; i++) {
            metal.push(static_cast<Metal>(rand() % 4));
            tempMetal.push(metal.top());
        }
        while(!tempMetal.empty()) {
            metals[tempMetal.top()]++;
            if(metals[tempMetal.top()]%5 == 0){
                colorOrder.push(metalToColor(tempMetal.top()));
            }
            tempMetal.pop();
        }
        factory->metalShipment(metal);
    }


    stack < Firework * > *customerFireworks = new stack<Firework *>();

    for(int i=0; i<numberOfPurchases; i++) {
        factory->sellFireworks(*customerFireworks, purchaseSize);
        for(int j=0; j<purchaseSize; j++){
            if(purchaseByColor[colorOrder.front()] > 0){
                purchaseByColor[colorOrder.front()]--;
                j--;
            }else {
                colorOrderPurchase.push(colorOrder.front());
            }
            colorOrder.pop();
        }

        if(sellByColor) {
            Color purchaseColor = static_cast<Color>(rand() % 4);
            factory->sellFireworks(*customerFireworks, purchaseSize, purchaseColor);
            purchaseByColor[purchaseColor] = purchaseByColor[purchaseColor] + purchaseSize;
            for (int j = 0; j < purchaseSize; j++) {
                colorOrderPurchase.push(purchaseColor);
            }
        }

    }


    bool pass = customerFireworks->size() == colorOrderPurchase.size();

    while (!customerFireworks->empty()) {
        if(pass && customerFireworks->top()->getColor() != colorOrderPurchase.top()){
            pass = false;
        }
        delete customerFireworks->top();
        customerFireworks->pop();
        colorOrderPurchase.pop();
    }

    delete customerFireworks;
    delete factory;

    return pass;
}

bool sample1() {

    // FIFO and LIFO
    // Take firework shipments and sell them. No memory management

    int numberOfShipments = 20;
    int sizeOfFireworkShipment = 20;
    int sizeOfMetalShipment = 0;
    int purchaseSize = 50;
    int numberOfPurchases = 5;

    bool pass = testFactory(numberOfShipments, sizeOfFireworkShipment, sizeOfMetalShipment, purchaseSize, numberOfPurchases, false);

    cout << "-end of sample1-" << endl;
    cout << (Firework::getTotalFireworks() - Firework::getHeapFireworks()) << " firework(s) remain on the stack" <<
    endl;
    cout << Firework::getHeapFireworks() << " firework(s) remain on the heap" << endl;

    if(pass) {
        cout << "Sample 1 ran without errors. Please submit for official results and score" << endl;
    }else{
        cout << "Did not pass Sample 1" << endl;
    }

    return pass;
}

bool sample2() {

    // Make fireworks from metal
    // Delete inventory in destructor

    int numberOfShipments = 20;
    int sizeOfFireworkShipment = 20;
    int sizeOfMetalShipment = 20;
    int purchaseSize = 50;
    int numberOfPurchases = 5;

    bool pass = testFactory(numberOfShipments, sizeOfFireworkShipment, sizeOfMetalShipment, purchaseSize, numberOfPurchases, false);

    cout << "-end of sample2-" << endl;
    cout << (Firework::getTotalFireworks() - Firework::getHeapFireworks()) << " firework(s) remain on the stack" <<
    endl;
    cout << Firework::getHeapFireworks() << " firework(s) remain on the heap" << endl;

    pass &= Firework::getHeapFireworks() == 0;

    if(pass){
        cout << "Sample 2 ran without errors. Please submit for official results and score" << endl;
    }else{
        cout << "Did not pass Sample 2" << endl;
    }
    return pass;
}


bool sample3() {

    // Sell Fireworks by color

    int numberOfShipments = 100;
    int sizeOfFireworkShipment = 50;
    int sizeOfMetalShipment = 20;
    int purchaseSize = 10;
    int numberOfPurchases = 20;

    bool pass = testFactory(numberOfShipments, sizeOfFireworkShipment, sizeOfMetalShipment, purchaseSize, numberOfPurchases, true);

    cout << "-end of sample3-" << endl;
    cout << (Firework::getTotalFireworks() - Firework::getHeapFireworks()) << " firework(s) remain on the stack" <<
    endl;
    cout << Firework::getHeapFireworks() << " firework(s) remain on the heap" << endl;

    if(pass){
        cout << "Sample 3 ran without errors. Please submit for official results and score" << endl;
    }else{
        cout << "Did not pass Sample 3" << endl;
    }
    return pass;
}

bool sample4() {

    // Sell fireworks by color in O(1)

    int numberOfShipments = 100;
    int sizeOfFireworkShipment = 50;
    int sizeOfMetalShipment = 20;
    int purchaseSize = 10;
    int numberOfPurchases = 20;

    bool pass = testFactory(numberOfShipments, sizeOfFireworkShipment, sizeOfMetalShipment, purchaseSize, numberOfPurchases, true);

    if(!pass){
        cout << "Did not pass test 3. Skiping efficiency test" << endl;
        return false;
    }

    numberOfShipments = 1000;
    sizeOfFireworkShipment = 1000;
    sizeOfMetalShipment = 500;
    purchaseSize = 50;
    numberOfPurchases = 100;

    FireworkFactory* factory = new FireworkFactory();

    stack < Firework * > fireworksToShip;
    stack <Metal> metal;

    for (int j = 0; j < numberOfShipments; j++) {
        for (int i = 0; i < sizeOfFireworkShipment; i++) {
            Color currentColor = j<10 ? Purple : static_cast<Color>(rand() % 3);
            Firework *firework = new Firework(currentColor);
            fireworksToShip.push(firework);
        }
        factory->fireworkShipment(fireworksToShip);

        for (int i = 0; i < sizeOfMetalShipment; i++) {
            metal.push(static_cast<Metal>(rand() % 3));
        }
        factory->metalShipment(metal);
    }

    stack < Firework * > *customerFireworks = new stack<Firework *>();

    clock_t startTime = clock();

    for(int i=0; i<numberOfPurchases; i++) {
        factory->sellFireworks(*customerFireworks, purchaseSize);
        Color purchaseColor =  i < 50 ? Purple : static_cast<Color>(rand() % 3);
        factory->sellFireworks(*customerFireworks, purchaseSize, purchaseColor);
    }

    double elapsedTime = (double(clock() - startTime) / CLOCKS_PER_SEC)*1000.0;

    while (!customerFireworks->empty()) {
        delete customerFireworks->top();
        customerFireworks->pop();
    }

    delete customerFireworks;
    delete factory;

    cout << "-end of sample4-" << endl;
    cout << "selling in sample4 ran in " << elapsedTime << "ms\n";
    cout << (Firework::getTotalFireworks() - Firework::getHeapFireworks()) << " firework(s) remain on the stack" <<
    endl;
    cout << Firework::getHeapFireworks() << " firework(s) remain on the heap" << endl;

    if(elapsedTime < 5){
        cout << "Sample 4 ran efficiently. Please submit for official results and score" << endl;
    }else{
        cout << "Did not pass Sample 4" << endl;
    }
    return pass;

}