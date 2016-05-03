//
// Created by filip on 4.4.2016.
//

#ifndef GRAFY_COLORTEST_H
#define GRAFY_COLORTEST_H

#include "../common.h"
#include "../Reader.h"
#include "../testers/ColoringTester.h"
#include "../Verifier.h"
#include "../ArgsParser.h"
#include "../testers/BruteForcer_C_10_6.h"

class ColorTest {
public:
    ColorTest( int argc, char *argv[] ){
        Reader * reader = new Reader();

        Verifier * verifier = new Verifier();
        ArgsParser * parser = new ArgsParser();

        string inputGraph = parser->parseColorTestArgs(argc, argv).first;
        string inputConfiguration = parser->parseColorTestArgs(argc, argv).second;

//        string inputGraph = (string)"./graphs/" + "petersen";
//        string inputConfiguration = "./configurations/C(10,6).txt";

        vector<vector<vector<int> > > graphs = reader->readGraphs(inputGraph);
        set<set<int> > configuration = reader->readStainerConfiguration(inputConfiguration);

        cout << "Graphs:\n";

        For(k, 0, graphs.size()){
            ColoringTester * tester = new BruteForcer_C_10_6();

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
                for(auto x: coloring) cout << "(" << x.first.first << " " <<  x.first.second << ") -> " << x.second << endl;

                if(verifier->checkSolution(graph, coloring, configuration)){
                    cout << "Result: YES\n";
                } else {
                    cout << "Wrong solution found\n";
                }
            }
            else cout << "Result: NO\n";

            double duration = (clock() - start) / (double) CLOCKS_PER_SEC;
            cout << "computed in: " << duration << " \n";
        }
    }
};


#endif //GRAFY_COLORTEST_H
