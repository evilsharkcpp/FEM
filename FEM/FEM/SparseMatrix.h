//#pragma once
//#include "headers/Matrix.h"
//#include <string>
//using namespace std;
//
//class SparseMatrix
//{
//   vector<int> ig;
//   vector<int> jg;
//   vector<double> di;
//   vector<double> gl;
//   vector<double> gu;
//   double* selector(int i, int j);
//public:
//   SparseMatrix();
//   SparseMatrix(vector<int> ia, vector<int> ja, size_t size);
//   double getValue(int i, int j);
//   void setValue(int i, int j, double value);
//   void addValue(int i, int j, double value);
//   vector<int> getColnsArray();
//   vector<int> getRowsArray();
//   size_t size();
//   void print(string filename = "out.txt");
//   void clear();
//};