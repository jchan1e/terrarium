#ifndef DATA_H
#define DATA_H

//#include <cmath>
#include <fstream>

class TimeSeries {
    std::vector<float> rows;
    int numberOfAnts;
    int width;

    TimeSeries(int numAnts, int W);
    ~TimeSeries();
    //void nextLine(float* points);
    void nextCoordinate(float* point);
    void writeAll(string filename);
}

#endif
