//
// Created by filip on 4.4.2016.
//

#ifndef GRAFY_REMOVABILITYTEST_H
#define GRAFY_REMOVABILITYTEST_H


#include "../Reader.h"
#include "../testers/ColoringTester.h"
#include "../Verifier.h"
#include "../ArgsParser.h"
#include "../testers/BruteForcer_C_10_6.h"

class RemovabilityTest {
public:
    RemovabilityTest( int argc, char *argv[] ){
        cout << "RemovabilityTest" << endl;

        Reader * reader = new Reader();
        ColoringTester * tester = new BruteForcer_C_10_6();
        Verifier * verifier = new Verifier();
        ArgsParser * parser = new ArgsParser();

//        string inputGraph = parser->parseColorTestArgs(argc, argv).first;
//        string inputConfiguration = parser->parseColorTestArgs(argc, argv).second;

        string inputGraph = (string)"./graphs/1/" + "5FLOWE3.34";
        string inputConfiguration = "./configurations/C(10,6).txt";

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

            vector<int> result;

            For(i, 0, graph.size()){
                cout << "testing removability of: " << i << endl;
                set<int> ignore;
                ignore.insert(i);

                if(tester->test(graph, configuration, true, &ignore)){
                    vector<pair<pair<int,int>, int> > coloring = tester->getColoring();

                    if(verifier->checkSolution(graph, coloring, configuration)){
                        cout << "Vertex: " << i << " is not removable." << endl;
                        cout << "Found coloring: " << endl;
                        for(auto x: coloring) cout << "(" << x.first.first << " " <<  x.first.second << ") -> " << x.second << endl;
                    } else {
                        cout << "Wrong solution found.\n";
                    }
                } else{
                    cout << "Found removable vertex: " << i << endl;
                    result.push_back(i);
                }
            }
            if(result.size() == 0) cout << "No removable vertices found." << endl;
            else {
                cout << "Found: " << endl;
                for(auto x: result) cout << x << " "; cout << endl;
            }

            double duration = (clock() - start) / (double) CLOCKS_PER_SEC;
            cout << "computed in: " << duration << " \n";
        }
    }
};


#endif //GRAFY_REMOVABILITYTEST_H
