
#ifndef GRAFY_READER_H
#define GRAFY_READER_H

#include "common.h"

using namespace std;

class Reader{

public:
    Reader(){

    }

    vector<vector<vector<int> > > readGraphs(string fileName){
        cout << "Reading graphs\n";

        fstream in (fileName);

        testComment(in);

        int n;
        in >> n;
        testComment(in);
        cout << "n = " << n << endl;

        vector<vector<vector<int> > > graphs;

        For(i, 0, n) graphs.push_back(readGraph(in));


        cout << "Reading successful\n";
        return graphs;
    }

    vector<vector<int> > readGraph(fstream &in) {

        int n;
        testComment(in);
    //    {char c; in >> c; cout << c << endl;}
        in >> n;
        testComment(in);
        in >> n;
        testComment(in);
        cout << n << "\n";


        vector<vector<int> > graph(n);

        For(i, 0, n){
            For(j, 0, 3){
                int x;
                in >> x;
                graph[i].push_back(x);
            }

        }



        return graph;
    }

    set<set<int> > readStainerConfiguration(string fileName){
        cout << "Reading configuration\n";
        fstream in (fileName);

        int n;
        in >> n;

        cout << n << "\n";

        set<set<int> > configuration;
        For(i, 0, n){
            set<int> block;
            For(j, 0, 3){
                int x;
                in >> x;
                block.insert(x);
            }
            configuration.insert(block);
        }

        cout << "Reading successful\n";
        return configuration;
    }

    void testComment(fstream &in){
    //    cout << "skusim najst koment\n";
        char c;
        in >> c;
        if(c == '{'){
            string s;
            getline(in, s);
     //       cout << "mazem: " << s;
            testComment(in);
        } else {
            in.putback(c);
        }
    }
};


#endif //GRAFY_READER_H
