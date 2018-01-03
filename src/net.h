#ifndef NET_H
#define NET_H

class Net {
public:
  int ni = 10;
  int n1 = 10;
  int no = 10;
  float* input;
  float* layer1;
  float* output;

  float** mati1;
  float** mat1o;

  Net(int Ni, int N1, int No, float** Mi1, float** M1o);
  ~Net();
  void setInput(float IN[]);
  void evaluate();
};

#endif
