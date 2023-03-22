#pragma once
#include <vector>
#include "Matrix.h"
#include "SparseMatrix.h"
#include<memory>
using namespace std;

class LOS
{
   std::shared_ptr<Matrix> a;
   vector<cType> x;
   vector<cType> b;
   vector<cType> r;
   vector<cType> z;
   vector<cType> p;
   int maxIterations;
   void multMatrixByVector(vector<cType>& res, std::shared_ptr<Matrix>& mat, vector<cType>& v);
   /*void multMatrixByVector(vector<cType>& res, SparseMatrix& mat, vector<cType>& v);*/
   cType scalar(vector<cType>& a, vector<cType>& b);
public:
   LOS();
   /*LOS(SparseMatrix& mat, vector<cType>& b, int iter);*/
   LOS(std::shared_ptr<Matrix>& mat, vector<cType>& b, int iter);
   void calculate(vector<cType>& x_start, cType eps = 1e-4);
   void getResult(vector<cType>& res);
   static cType norm(vector<cType>& x);
};