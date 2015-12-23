
#include "../common.h"
#include "ColoringTester.h"

using namespace std;

class BruteForcer_C_10_6 : public ColoringTester {
public:
    BruteForcer_C_10_6(){ }

    vector<pair<int,int> > edges;
    vector<vector<int> > graph;
    set<set<int> > config;
    unordered_map<pair<int, int>, int, pairhash> twoColorDefineThird;
    unordered_map<int, set<int> > usedColorsAroundVertex;
    unordered_map<int, int> colorForEdge;
    vector<vector<pair<pair<int,int>, int> > > colorings;
    map<set<int>, set<int> > possibleColors;
    set<int> allColors, empty, forStart;
    int numberOfColors;
    int lookUps = 0;

    bool test(const vector<vector<int> > graph_, const set<set<int> > config_){

        cout << "preparing" << endl;

        graph = graph_;
        config = config_;
        edges = getEdges();

//        cout << "edges:\n";
//        for(auto x: edges) cout << x.first << " " << x.second << endl;
//        return true;

        prepareContainers();
        countPossibleColors();
  //      cout << "number of colors = " << numberOfColors << endl;
        bool result = tryToColor(0);
        cout << "number of look ups = " << lookUps << endl;
        return result;
    }

    vector<pair<pair<int,int>, int> > getColoring() {
        return colorings[0];
    }

private:
    void prepareContainers(){
        usedColorsAroundVertex.clear();
        colorForEdge.clear();
        twoColorDefineThird.clear();
        numberOfColors = -1;

        for(auto i: config){
            vector<int> c;
            for(auto x: i) {
                c.push_back(x);
                numberOfColors = max(numberOfColors, x+1);
            }
            twoColorDefineThird[{c[0], c[1]}] = c[2];
            twoColorDefineThird[{c[0], c[2]}] = c[1];
            twoColorDefineThird[{c[1], c[2]}] = c[0];
        }
        For(i, 0, numberOfColors) allColors.insert(i);

        forStart.insert(0);
        forStart.insert(1);
    }

    void countPossibleColors(){
        //for one color
        For(i, 0, numberOfColors){
            set<int> group, pos;
            group.insert(i);
            for(auto b: config){
                if(b.find(i) != b.end()){
                    for(auto c: b) pos.insert(c);
                }
            }
            pos.erase(i);
            possibleColors[group] = pos;
        }

        //for 2 colors
        For(i, 0, numberOfColors)
            For(j, 0, numberOfColors){
                if(i == j) continue;
                set<int> group, group2,pos, pos2;
                group.insert(i);
                group2.insert(j);
                pos = possibleColors[group];
                pos2 = possibleColors[group2];
                for(auto x: pos){
                    if(pos2.find(x) == pos2.end()) pos.erase(x);
                }
                group.insert(j);
                possibleColors[group] = pos;
            }

     /*   for(auto a: possibleColors){
            cout << "for: {"; for(auto x: a.first) cout << x << " "; cout << "} -> ";
            for(auto x: a.second) cout << x << " "; cout << endl;
        }*/
    }


    void findAndAddShortWay(vector<vector<int>> &g, unordered_set<pair<int, int>, pairhash> &usedEdges,
                            unordered_set<int> &usedVerices, vector<pair<int, int> > &res) {
        vector<int> dist(g.size());
        For(i, 0, dist.size()) dist[i] = 1 << 30;

        queue<pair<int, int> > qe;
        for(auto x: usedVerices) qe.push({x, 0});

        while(!qe.empty()){
            pair<int,int> p = qe.front();
            qe.pop();

            if(dist[p.first] <= p.second) continue;
            dist[p.first] = p.second;

            for(auto x: g[p.first]){
                qe.push({x, p.second + 1});
            }
        }

        int minDist = 1 << 30;
        for(int i = 0 ; i < g.size(); i++){
            for(auto j: g[i]){
                pair<int,int> p = {i, j};
                if(usedEdges.find(p) != usedEdges.end() || usedEdges.find({p.second, p.first}) != usedEdges.end()) continue;
                minDist = min(minDist, dist[i] + dist[j]);
            }
        }

        for(int i = 0 ; i < g.size(); i++){
            for(auto j: g[i]){
                pair<int,int> p = {i, j};
                if(usedEdges.find(p) != usedEdges.end() || usedEdges.find({p.second, p.first}) != usedEdges.end()) continue;
                if(dist[i] + dist[j] == minDist){
                    res.push_back({i, j});
                    usedEdges.insert(res.back());
                    usedVerices.insert(i);
                    usedVerices.insert(j);
                }
            }
        }

        return;
    }

    vector<pair<int,int> > getEdges(){
        cout << "Sorting edges\n";
        unordered_set<pair<int, int>, pairhash> usedEdges;
        unordered_set<int> usedVertices;
        vector<vector<int> > g = graph;
        vector<pair<int,int> > res;

        srand((unsigned int) time(NULL));
        usedVertices.insert(rand() % g.size());
        cout << "Random start point: " << *usedVertices.begin() << endl;

        cout << "start\n";
        while(usedEdges.size() < g.size()*3/2) {
          //  cout << "res size = " << res.size() << endl;
            findAndAddShortWay(g, usedEdges, usedVertices, res);
        }


     /*   For(i, 0, graph.size()){
            For(j, 0, graph[i].size()){
                pair<int,int> p = {i, graph[i][j]};
                if(used.find(p) != used.end() || used.find({p.second, p.first}) != used.end()) continue;
                if(p.first <= p.second) res.push_back(p);
                else res.push_back({p.second, p.first});
                used.insert(p);
            }
        }*/
        cout << "Successfull\n";
        return res;
    }

    set<int> &getPossibleColors(int k){
        if(k < 2) return forStart;

        pair<int,int> edge = edges[k];
        set<int> around = usedColorsAroundVertex[edge.first];
        for(auto x: usedColorsAroundVertex[edge.second]) around.insert(x);
        if(around.size() == 0 ) return allColors;
        else if(around.size() < 3) return possibleColors[around];
        else return empty;
    }

    int onlyOneOption(int v){
        set<int> usedAround = usedColorsAroundVertex[v];

        if(usedAround.size() == 2){
            set<int> res = possibleColors[usedAround];
            if(res.size() == 1) return *res.begin();
        }
        return -1;
    }

    vector<pair<pair<int,int>, int> > getLastColoring() {
        vector<pair<pair<int,int>, int> > res(edges.size());
        for(auto x: colorForEdge) res[x.first] = {edges[x.first], x.second};
        return res;
    }

    void saveColoring(){
        colorings.push_back(getLastColoring());
    }

    void setColor(int color, int k){
        pair<int,int> edge = edges[k];
  //      cout << "setting " << color << " for " << k << endl;
        colorForEdge[k] = color;
        usedColorsAroundVertex[edge.first].insert(color);
        usedColorsAroundVertex[edge.second].insert(color);
    }

    void clearColor(int color, int k){
        pair<int,int> edge = edges[k];
 //       cout << "clearing " << color << " for " << k << endl;
        colorForEdge.erase(k);
        usedColorsAroundVertex[edge.first].erase(color);
        usedColorsAroundVertex[edge.second].erase(color);
    }

    bool coloringIsOk(int k){
        pair<int,int> p = edges[k];

        set<int> around = usedColorsAroundVertex[p.first];
        if(around.size() == 3 && config.find(around) == config.end()) return false;

        around = usedColorsAroundVertex[p.second];
        if(around.size() == 3 && config.find(around) == config.end()) return false;

        return true;
    }

    bool setColorAndTryNext(int color, int k){
        pair<int,int> p = edges[k];
        if(usedColorsAroundVertex[p.first].find(color) != usedColorsAroundVertex[p.first].end()) return false;
        if(usedColorsAroundVertex[p.second].find(color) != usedColorsAroundVertex[p.second].end()) return false;

        setColor(color, k);
  //      cout << "color: " << color << " k = " << k << endl;
        bool res = coloringIsOk(k) && tryToColor(k+1);
        clearColor(color, k);
        return res;
    }

    bool tryToColor(int k){
        if(lookUps % 100000 == 0) cout << k << " " << lookUps<< endl;
        lookUps ++;
        if(!colorings.empty()) return false;
        if(k == edges.size()){
  //          cout << "OK\n";
            saveColoring();
            return true;
        }
   //     cout << "k = " << k << endl;
        pair<int,int> edge = edges[k];

        int colorForFirst = onlyOneOption(edge.first);
        int colorForSecond = onlyOneOption(edge.second);

        if(colorForFirst != -1 && colorForSecond != -1 && colorForFirst != colorForSecond) return false;

        if(colorForFirst != -1) return setColorAndTryNext(colorForFirst, k);

        if(colorForSecond != -1) return setColorAndTryNext(colorForSecond, k);

        set<int> &possibilities = getPossibleColors(k);

    //    For(color, 0, numberOfColors){
        for(auto color: possibilities){
   //         cout << "trying " << color << " for " << k << endl;
            if(setColorAndTryNext(color, k)){
   //             cout << "OKK\n";
                return true;
            }
        }
   //     cout << "skoncil som v " << k << endl;
        return false;
    }
};
