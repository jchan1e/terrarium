#include "data.h"

using namespace std;

TimeSeries::TimeSeries(int numAnts, int W) {
    numberOfAnts = numAnts;
    width = W;
    rows.append(numberOfAnts);
}

TimeSeries::~TimeSeries();

// void TimeSeries::nextLine(float* points){
//
// }

void TimeSeries::nextCoordinate(float x, float y, float z){
    rows.push_back(x);
    rows.push_back(y);
    rows.push_back(z);
}

void TimeSeries::writeAll(string filename) {
    for (float s : rows) {
        cout<<s<<" "<<endl;
    }
}
