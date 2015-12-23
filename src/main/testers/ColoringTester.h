//
// Created by filip on 23.12.2015.
//

#ifndef GRAFY_COLORINGTESTER_H
#define GRAFY_COLORINGTESTER_H

#include "../common.h"

using namespace std;

class ColoringTester {
public: virtual bool test(const vector<vector<int> > graph_, const set<set<int> > config_) = 0;
    virtual vector<pair<pair<int,int>, int> > getColoring() = 0;
};


#endif //GRAFY_COLORINGTESTER_H
