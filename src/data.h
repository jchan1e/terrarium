#ifndef DATA_H
#define DATA_H

#include <nholmann/json.hpp>
#include <cmath>
#include <fstream>

class Data {
    Data();
    ~Data();

    json readJson(string filename);
    void writeJson(string filename);

    

}
