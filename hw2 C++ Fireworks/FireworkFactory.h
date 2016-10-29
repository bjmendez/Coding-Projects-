#ifndef HW2_FIREWORKFACTORY_H
#define HW2_FIREWORKFACTORY_H

#include <stack>
#include <queue>
#include <vector>

#include "Firework.h"

class FireworkFactory {
//Instance variables
private:
    queue<Firework*> inventory;
    //A queue for every color allows for a spefific color to be sold in O(1)
    queue<Firework*> orange;
    queue<Firework*> green;
    queue<Firework*> blue;
    queue<Firework*> purple;
    //A queue for order of when each firework came in allows for them to be sold by their age by just looking at the front of the queue to see which is the oldest
    queue<int> orangeorder;
    queue<int> greenorder; 
    queue<int> blueorder;
    queue<int> purpleorder;
    int Calcium =0;
    int coppersu = 0;
    int copperch = 0;
    int potassium=0;
    int count = 0;
    int i = 0; 
    // TODO: Track quantities of metals
    // TODO: Track finished fireworks in the proper order

public:
    FireworkFactory();

    // Point 1
    void fireworkShipment(stack<Firework*>&);
    void sellFireworks(stack<Firework*>&, int quantity);

    // Point 2
    void metalShipment(stack<Metal>&);
    ~FireworkFactory();

    // Point 3 for correctness, Point 4 for O(1) runtime
    void sellFireworks(stack<Firework*>&, int quantity, Color color);
};


#endif //HW2_FIREWORKFACTORY_H
