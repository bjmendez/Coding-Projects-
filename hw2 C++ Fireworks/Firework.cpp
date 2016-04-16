#include "Firework.h"

// Toggle debug cout statements here. Off by default to reduce console clutter. If turned on, it's recommended to only
// run sampleUsage()
bool Firework::coutOn = false;

bool Firework::isCoutOn(){
    return Firework::coutOn;
}


/*** Functionality code ***/

Color Firework::getColor() const{
    return this->color;
}

Firework::Firework(Color color){
    if(Firework::coutOn) {
        cout << "made " << colorToString(color) << " firework" << endl;
    }
    Firework::totalFireworks++;
    this->color = color;
    this->fuse = new Fuse();
}


/*** Helper Functions ***/

string colorToString(Color color){
    switch(color){
        case 0:
            return "Orange";
        case 1:
            return "Green";
        case 2:
            return "Blue";
        case 3:
            return "Purple";
        default:
            return "Color Not Found";
    }
}

Color metalToColor(Metal metal){
    switch(metal){
        case 0:
            return Orange;
        case 1:
            return Green;
        case 2:
            return Blue;
        case 3:
            return Purple;
    }
    cerr << "Something went wrong in metalToColor" << endl;
    return Orange;
}


Fuse::Fuse(){
    this->length = 10;
}


/*** Memory tracking code below. No need to read except for curiosity ***/

int Firework::totalFireworks=0;
int Firework::heapFireworks=0;


int Firework::getTotalFireworks(){
    return Firework::totalFireworks;
}

int Firework::getHeapFireworks(){
    return Firework::heapFireworks;
}

void* Firework::operator new(std::size_t sz) {
    if(Firework::coutOn){
            cout << "firework created dynamically on the heap: ";
    }
    Firework::heapFireworks++;
    return ::operator new(sz);
}

Firework::~Firework() {
    delete this->fuse;
    if(Firework::coutOn) {
        cout << "lit " << colorToString(color) << " firework.. BOOM!" << endl;
    }
    Firework::totalFireworks--;
}

void Firework::operator delete(void* object){
    if(Firework::coutOn) {
        cout << "-it was launched with delete-\n";
    }
    Firework::heapFireworks--;
}

Firework::Firework(const Firework& other) : color(other.getColor()){
    this->fuse = new Fuse();
    if(Firework::coutOn) {
        cout << "Made a firework with the copy constructor" << endl;
    }
    Firework::totalFireworks++;
}

Firework& Firework::operator=(const Firework& rhs){
    // Copy color. Keep the old fuse
    color = rhs.getColor();
    if(Firework::coutOn) {
        cout << "Copied a firework with the copy assignment operator" << endl;
    }
    return *this;
}