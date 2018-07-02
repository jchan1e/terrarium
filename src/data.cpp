#include "data.h"

using namespace std;

TimeSeries::TimeSeries(int numAnts, int W) {
    numberOfAnts = numAnts;
    width = W;
    rows.push_back(numberOfAnts);
}

TimeSeries::~TimeSeries(){}

// void TimeSeries::nextLine(float* points){
//
// }

void TimeSeries::nextCoordinate(float x, float y, float z){
    rows.push_back(x);
    rows.push_back(y);
    rows.push_back(z);
}

void TimeSeries::writeAll(string filename) {
    ofstream outfile(filename, ofstream::binary);
    outfile.write((char*)&numberOfAnts, sizeof(int));
    outfile.write((char*)&width, sizeof(int));
    outfile.write((char*)rows.data(), rows.size()*sizeof(float));
    outfile.close();
    //for (float s : rows) {
    //    cout<<s<<" "<<endl;
    //}
}
