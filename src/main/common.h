#pragma once

#ifndef GRAFY_COMMON_H
#define GRAFY_COMMON_H

#include <vector>
#include <set>
#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <dirent.h>
#include <ctime>
#include <queue>

#define For(i, from, to) for(int (i) = (from); (i) < (to); (i)++)

using namespace std;

struct pairhash {
public:
    template <typename T, typename U>
    std::size_t operator()(const std::pair<T, U> &x) const
    {
        return std::hash<T>()(x.first) ^ std::hash<U>()(x.second);
    }
};

#endif //GRAFY_COMMON_H
