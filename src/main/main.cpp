

#include "Reader.h"
#include "Verifier.h"
#include "testers/BruteForcer.h"
#include "testers/BruteForcer_C_10_6.h"
#include "ArgsParser.h"

using namespace std;

int main( int argc, char *argv[] ) {

    Reader * reader = new Reader();
    ColoringTester * tester = new BruteForcer_C_10_6();
    Verifier * verifier = new Verifier();
    ArgsParser * parser = new ArgsParser();

    string inputGraph = parser->parse(argc, argv).first;
    string inputConfiguration = parser->parse(argc, argv).second;

//    string inputGraph = (string)"./graphs/" + "5FLOWE3.58";
//    string inputConfiguration = "./configurations/C(10,6).txt";

    vector<vector<vector<int> > > graphs = reader->readGraphs(inputGraph);
    set<set<int> > configuration = reader->readStainerConfiguration(inputConfiguration);

    cout << "Graphs:\n";

    For(k, 0, graphs.size()){

        cout << endl << "Graph number: " << k + 1 << endl;
        vector<vector<int> > graph = graphs[k];

        if(!verifier->checkGraph(graph)){
            cout << "Wrong graph" << endl;
            continue;
        }

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
    }


    return 0;
}