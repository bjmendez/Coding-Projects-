#ifndef HW2_FIREWORK_H
#define HW2_FIREWORK_H

#include <iostream>

using namespace std;


enum Metal{
    CalciumChloride,   // 0: Orange
    CopperSulfate,     // 1: Green
    CopperChloride,    // 2: Blue
    PotassiumChloride  // 3: Purple
};


enum Color{
    Orange, // 0
    Green,  // 1
    Blue,   // 2
    Purple  // 3
};

// helper functions
string colorToString(Color color);
Color metalToColor(Metal);


// Basic class that will be used for pointer and memory management
class Fuse{
private:
    int length;
public:
    Fuse();
};


class Firework {

private:

    // Color of the firework
    Color color;

    // Since Fuse is a member variable that is a pointer we must be careful how we manage it.
    Fuse* fuse;

    // keeps track of the total number of fireworks in existence
    static int totalFireworks;
    static int heapFireworks;

    // toggle for debug statements
    static bool coutOn;

public:

    // Constructor to define the Color of the firework
    Firework(Color);

    // getter for the firework color
    Color getColor() const;


    // getter for coutOn
    static bool isCoutOn();




    // The functions below track the memory management of fireworks. It is not required to understand them all for this
    // assignment.

    static int getTotalFireworks();
    static int getHeapFireworks();
    void* operator new(std::size_t sz);
    void operator delete(void*);
    ~Firework();
    Firework(const Firework&);
    Firework& operator=(const Firework&);
};


#endif //HW2_FIREWORK_H
