

#include "Reader.h"
#include "BruteForcer.h"
#include "common.h"
#include "Verifier.h"

using namespace std;

int main() {

    Reader * reader = new Reader();
    BruteForcer * tester = new BruteForcer();
    Verifier * verifier = new Verifier();

    string inputGraph = "./../graphs/SS7-1.34";
    string inputConfiguration = "./../configurations/C(10,6).txt";

//    string inputGraph = "./../graphs/g1.txt";
//    string inputConfiguration = "./../configurations/conf1.txt";

    vector<vector<vector<int> > > graphs = reader->readGraphs(inputGraph);
    set<set<int> > configuration = reader->readStainerConfiguration(inputConfiguration);

    cout << "graph:\n";

    vector<vector<int> > graph = graphs[0];
    For(i, 0, graph.size()){
        cout << i << ": ";
        For(j, 0, graph[i].size()) cout << graph[i][j] << " "; cout << endl;
    }

    cout << "configuration:\n";
    for(auto i: configuration){
        for(auto x: i) cout << x << " "; cout << endl;
    }

    clock_t start = clock();

    if(tester->test(graph, configuration)){
        vector<pair<pair<int,int>, int> > coloring = tester->getColoring();

        if(verifier->checkSolution(graph, coloring, configuration)){
            cout << "Result: YES\n";
            for(auto x: coloring) cout << "(" << x.first.first << " " <<  x.first.second << ") -> " << x.second << endl;
        } else {
            cout << "Wrong solution found\n";
        }
    }
    else cout << "Result: NO\n";

    double duration = (clock() - start) / (double) CLOCKS_PER_SEC;
    cout << "computed in: " << duration << " \n";

    return 0;
}