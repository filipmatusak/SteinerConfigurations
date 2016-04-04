
#include "../common.h"
#include "ColoringTester.h"

using namespace std;

class BruteForcer_C_10_6 : public BruteForcer {
public:
    BruteForcer_C_10_6(){ }

    set<int> forStart;

    void prepareContainers(){
        BruteForcer::prepareContainers();

        forStart.insert(0);
        forStart.insert(1);
    }

    set<int> &getPossibleColors(int k){
        if(k < 2) return forStart;
        BruteForcer::getPossibleColors(k);
    }
};
