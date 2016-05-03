#pragma once

#include "../common.h"
#include "ColoringTester.h"
#include "BruteForcer.h"

using namespace std;

class BruteForcer_C_10_6 : public BruteForcer {
public:
    BruteForcer_C_10_6(){ }

    set<int> forStart;

    void prepareContainers(){
        BruteForcer::prepareContainers();

     //   cout << "virtual prepare\n";
        forStart.insert(0);
        forStart.insert(1);
    }

    set<int> &getPossibleColors(int k){
     //   cout << "virtual get possibilities\n";

        if(k < 2) return forStart;
        BruteForcer::getPossibleColors(k);
    }
};
