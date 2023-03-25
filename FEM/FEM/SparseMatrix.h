#pragma once
#include "headers/Matrix.h"
#include <string>
using namespace std;

class SparseMatrix : public Matrix
{
   vector<int> ig;
   vector<int> jg;
   vector<double> di;
   vector<double> gl;
   vector<double> gu;
   double* selector(int i, int j);
public:
   SparseMatrix();
   SparseMatrix(SparseMatrix& a)
   {
      _n = a.getSize();
      ig = vector<int>(a.ig);
      jg = vector<int>(a.jg);
      di = vector<double>(a.di);
      gl = vector<double>(a.gl);
      gu = vector<double>(a.gu);
   }
   SparseMatrix(const SparseMatrix* a)
   {
      _n =  (*a).getSize();
      ig = vector<int>((*a).ig);
      jg = vector<int>((*a).jg);
      di = vector<double>((*a).di);
      gl = vector<double>((*a).gl);
      gu = vector<double>((*a).gu);
   }
   SparseMatrix(vector<int> ia, vector<int> ja, size_t size);
   cType& operator()(int i, int j) override;
   const cType& operator()(int i, int j) const override;
   std::shared_ptr<Matrix> operator+(const Matrix& a) const override;
   std::shared_ptr<Matrix> operator-(const Matrix& a) const override;
   std::shared_ptr<Matrix> operator+(const cType& a) const override;
   std::shared_ptr<Matrix> operator-(const cType& a) const override;
   std::shared_ptr<Matrix> operator*(const Matrix& a) const override;
   std::shared_ptr<Matrix> operator*(const cType& a) const override;
   double getValue(int i, int j);
   void setValue(int i, int j, double value);
   void addValue(int i, int j, double value);
   vector<int> getColnsArray();
   vector<int> getRowsArray();
   size_t size();
   void print(string filename = "out.txt");
   void clear();
};