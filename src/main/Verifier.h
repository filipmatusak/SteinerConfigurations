//
// Created by filip on 22.11.2015.
//

#ifndef GRAFY_VERIFIER_H
#define GRAFY_VERIFIER_H

#include "common.h"

using namespace std;

class Verifier {
public:
    Verifier(){

    }

    bool checkSolution(vector<vector<int> > &graph,
                       vector<pair<pair<int,int>, int> > &coloring,
                       set<set<int> > &configuration){
        vector<set<int> > colorsForVertex(graph.size());
        For(i, 0, coloring.size()){
            pair<int,int> edge = coloring[i].first;
            int color = coloring[i].second;
            colorsForVertex[edge.first].insert(color);
            colorsForVertex[edge.second].insert(color);
        }

        For(i, 0, graph.size()){
      //      cout << "i: " << i << " -> "; for(auto x: colorsForVertex[i]) cout << x << " "; cout << endl;
            if(colorsForVertex[i].size() != 3) return false;
            if(configuration.find(colorsForVertex[i]) == configuration.end()) return false;
        }
        return true;
    }
};


#endif //GRAFY_VERIFIER_H
