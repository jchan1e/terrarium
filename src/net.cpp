#include "net.h"

Net::Net(int Ni, int N1, int No, float** Mi1, float** M1o) {
  ni = Ni;
  n1 = N1;
  no = No;
  mati1 = Mi1;
  mat1o = M1o;

  input  = new float[ni];
  layer1 = new float[n1];
  output = new float[no];
}

Net::~Net() {
  delete input;
  delete layer1;
  delete output;
}

void Net::setInput(float IN[]) {
  //sizes assumed to match, otherwise segfaults may occur
  for(int i=0; i < ni; ++i)
    input[i] = IN[i];
}

void dot(int n1, int n2, float* inm, float** mat, float* outm) {
  for(int j=0; j < n2; ++j) {
    float s = 0.0;
    for(int i=0; i < n1; ++i)
      s += inm[i] * mat[i][j];
    outm[j] = s;
  }
}

void Net::evaluate() {
  dot(ni, n1, input,  mati1, layer1);
  dot(n1, no, layer1, mat1o, output);
}
