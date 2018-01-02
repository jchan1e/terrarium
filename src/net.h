#ifndef NET_H
#define NET_H

class Net {
public:
   const int ni = 10;
   const int n1 = 10;
   const int no = 10;
   float* input;
   float* layer1;
   float* output;

   float** mati1;
   float** mat1o;

   Net(int Ni, int N1, int No, float** Mi1, float** M1o);
   ~Net();
   void setInput(float IN[10]);
   void evaluate();
};

#endif
