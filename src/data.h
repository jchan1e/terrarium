#ifndef DATA_H
#define DATA_H

#include <fstream>
#include <string>
#include <vector>

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
