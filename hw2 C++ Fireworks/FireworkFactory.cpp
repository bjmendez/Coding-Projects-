#include "FireworkFactory.h"

FireworkFactory::FireworkFactory(){
    
}
// Receive a stack of Firework pointers and add them to the factories inventory. Fireworks must be sold in the order
// that they are popped off the stack (The top of the stack is the oldest firework).
void FireworkFactory::fireworkShipment(stack<Firework*>& fireworkShipment){
	 
	while(!fireworkShipment.empty()){
	   // Add fireworks to their respective color queues by keep track of their age using i and the queue for their order
	   if(fireworkShipment.top()->getColor() == Orange){
            orange.push(fireworkShipment.top());
            orangeorder.push(i);
            i++;
        }
        else if(fireworkShipment.top()->getColor() == Green){
            green.push(fireworkShipment.top());
            greenorder.push(i);
            i++;
            }
        else if(fireworkShipment.top()->getColor() == Blue){
            blue.push(fireworkShipment.top());
            blueorder.push(i);
            i++;
            }
        else if(fireworkShipment.top()->getColor() == Purple){
            purple.push(fireworkShipment.top());
            purpleorder.push(i);
            i++;
        }        
    fireworkShipment.pop();
	}
}

// Sell quantity fireworks by pushing them onto the customerStack with the oldest fireworks being sold first (FIFO).
void FireworkFactory::sellFireworks(stack<Firework*>& customerStack, int quantity){
   // To sell the oldest firework of all the color queues we just look at the lowest number in the front of the queue
   while(quantity > 0){
        if(orangeorder.front() < greenorder.front() && orangeorder.front() < blueorder.front() && orangeorder.front() <purpleorder.front()){
    	   customerStack.push(orange.front());
            orange.pop();
            quantity--;
            orangeorder.pop();
        }
        else if(greenorder.front() < orangeorder.front() && greenorder.front() <blueorder.front() && greenorder.front() < purpleorder.front()){
            customerStack.push(green.front());
            green.pop();
            quantity--;
            greenorder.pop();
        }
        else if(blueorder.front() < orangeorder.front() && blueorder.front() < greenorder.front() && blueorder.front() < purpleorder.front()){
            customerStack.push(blue.front());
            blue.pop();
            quantity--;
            blueorder.pop();
        }
        else if(purpleorder.front() < orangeorder.front() && purpleorder.front() < greenorder.front() && purpleorder.front() < blueorder.front()){
            customerStack.push(purple.front());
            purple.pop();
            quantity--;
            purpleorder.pop();
        }
            
    }
}

// Before destroying the factory you must properly dispose of all the fireworks in your inventory (On the heap).
FireworkFactory::~FireworkFactory(){
    
   while(!orange.empty()){
        delete orange.front();
        orange.pop();  
    }
    while(!green.empty()){
        delete green.front();
        green.pop();
    }
    while(!blue.empty()){
        delete blue.front();
        blue.pop();
    }
    while(!purple.empty()){
        delete purple.front();
        purple.pop();
    }
}

// Receive a shipment of metal which will be used to make new fireworks in the factory. Whenever the factory has 5 of
// any type of metal it must immediately make a firework of the corresponding color and add it to the inventory.
// To make a firework, you must use the new keyword to create it dynamically on the heap and manage a pointer to
// the firework.
void FireworkFactory::metalShipment(stack<Metal>& metalShipment){
    // TODO
    //If the top of a metalshipment equals a certain metal increment its counter and when it reaches 5 make a new firework of that color
    while(!metalShipment.empty()){
    
        if(metalShipment.top()  == CalciumChloride){
            Calcium++;
            metalShipment.pop();
            if(Calcium == 5){
                Firework *orang = new Firework(Orange);
                orange.push(orang);
                orangeorder.push(i);
                Calcium =0;
                i++;
            }
        }
        else if(metalShipment.top() == CopperSulfate){
            coppersu++;
            metalShipment.pop();
            if(coppersu == 5){
                Firework *gree = new Firework(Green);
                green.push(gree);
                greenorder.push(i);
                coppersu =0;
                i++;
            }
        }
        else if(metalShipment.top() == CopperChloride){
            copperch++;
            metalShipment.pop();
            if(copperch == 5){
                Firework *blu = new Firework(Blue);
                blue.push(blu);
                blueorder.push(i);
                copperch =0; 
                i++;
            }
        }
        else if(metalShipment.top() == PotassiumChloride){
            potassium++;
            metalShipment.pop();
            if(potassium == 5){
                Firework *purp = new Firework(Purple);
                purple.push(purp);
                purpleorder.push(i);
                potassium =0;
                i++;
            }
        }

    }
   
}

// A customer is purchasing quantity fireworks, but they must all be of the color specified by the customer. The order
// in which the fireworks are sold must be maintained (FIFO), but fireworks of the specified color can be sold before
// other colors if there is no other way to fulfil the order. Be sure not to sell the same firework more than once with
// either of the sellFireworks functions.
//
// For the efficient point of this assignment, this function must run in O(quantity) time. If only 1 firework is being
// purchased, the runtime must be O(1) regardless of where the firework to be sold is in the inventory.
void FireworkFactory::sellFireworks(stack<Firework*>& customerStack, int quantity, Color color){
   //All fireworks have their respective color queues so getting them in O(1) just involves popping the front.
   // Order is maintained by also pushing the queue keeping order so that we know that firework is gone if we wanted to sell by oldest again	
    while(quantity > 0){
        if(orange.front()->getColor() == color){
            quantity--;
            customerStack.push(orange.front());
            orange.pop();
            orangeorder.pop();   
               
        }
        else if(green.front()->getColor() == color){
            quantity--;
            customerStack.push(green.front()); 
            green.pop();
            greenorder.pop();   
            
        }
        else if(blue.front()->getColor() == color){          
            quantity--;
            customerStack.push(blue.front());
            blue.pop();
            blueorder.pop();
            
        }
        else if(purple.front()->getColor() == color){
            quantity--;
            customerStack.push(purple.front());
            purple.pop();
            purpleorder.pop();
            
        }
    }    
}


