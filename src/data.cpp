#include "data.h"

using namespace std;

TimeSeries::TimeSeries(int numAnts, int W) {
    numberOfAnts = numAnts;
    width = W;

}

TimeSeries::~TimeSeries();

// void TimeSeries::nextLine(float* points){
//
// }

void TimeSeries::nextCoordinate(float* point){
    rows.insert(rows.end(), point);
}

void TimeSeries::writeAll(string filename);
