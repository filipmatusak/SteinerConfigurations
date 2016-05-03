//
// Created by filip on 13.1.2016.
//

#ifndef GRAFY_ARGSPARSER_H
#define GRAFY_ARGSPARSER_H

#include "common.h"

using namespace std;

class ArgsParser {
public:
    ArgsParser(){}

    pair<string, string> parseColorTestArgs(int argc, char **argv){
        if(argc != 3){
            cout << "zadaj cestu ku grafu a konfiguracii ako parametre" << endl;
            exit(-1);
        }
        return { (string)argv[1], (string)argv[2] };
    };
};


#endif //GRAFY_ARGSPARSER_H
