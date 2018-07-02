#ifndef DATA_H
#define DATA_H

//#include <cmath>
#include <fstream>
#include <string>

class TimeSeries {
private:
    std::vector<float> rows;
    int numberOfAnts;
    int width;
public:
    TimeSeries(int numAnts, int W);
    ~TimeSeries();
    //void nextLine(float* points);
    void nextCoordinate(float x, float y, float z);
    void writeAll(std::string filename);
};

#endif
