#include "headers/LOS.h"
using namespace std;

cType LOS::norm(vector<cType>& x){
   cType res = 0;
   for (int i = 0; i < x.size(); i++) {
      res += x[i] * x[i];
   }
   return sqrt(res);
}

//for sparse matrix
//void LOS::multMatrixByVector(vector<cType>& res, SparseMatrix& mat, vector<cType>& v)
//{
//   auto jg = mat.getColnsArray();
//   auto ig = mat.getRowsArray();
//
//   for (int i = 0; i < res.size(); i++)
//   {
//      for (int indI = ig[i]; indI < ig[i + 1]; indI++)
//      {
//         int indJ = jg[indI];
//         res[i] += mat.getValue(i, indJ) * v[indJ];
//         res[indJ] += mat.getValue(indJ, i) * v[i];
//      }
//      res[i] += mat.getValue(i, i) * v[i];
//   }
//}

void LOS::multMatrixByVector(vector<cType>& res, std::shared_ptr<Matrix>& mat, vector<cType>& v) {
   for (size_t i{ 0 }; i < res.size(); i++) {
      for (size_t j{ 0 }; j < res.size(); j++) {
         res[i] += (*mat)[i][j] * v[j];
      }
   }
}

cType LOS::scalar(vector<cType>& a, vector<cType>& b) {
   cType sum = 0;
   for (int i = 0; i < a.size(); i++) {
      sum += a[i] * b[i];
   }
   return sum;
}
   LOS::LOS() : a({})
   {
      maxIterations = 0;
   }

  /* LOS::LOS(Matrix& mat, vector<cType>& b, int iter)
   {
      a = Matrix(mat);
      this->b = vector<cType>(b);
      r.resize(b.size());
      z.resize(b.size());
      p.resize(b.size());
      x.resize(b.size());
      maxIterations = iter;
   }*/

   LOS::LOS(std::shared_ptr<Matrix>& mat, vector<cType>& b, int iter) {
      a = mat;
      this->b = vector<cType>(b);
      r.resize(b.size());
      z.resize(b.size());
      p.resize(b.size());
      x.resize(b.size());
      maxIterations = iter;
   }

   void LOS::calculate(vector<cType>& x_start, cType eps) {

      multMatrixByVector(r, a, x_start);
      for (int i = 0; i < r.size(); i++) {
         r[i] = b[i] - r[i];
         z[i] = r[i];
      }
      multMatrixByVector(p, a, z);
      cType disp = 1;
      for (int k = 1; k <= maxIterations && disp > eps; k++) {
         cType alpha = scalar(p, r) / scalar(p, p);
         for (int i = 0; i < x.size(); i++) {
            x[i] += alpha * z[i];
            r[i] -= alpha * p[i];
         }
         vector<cType> tmp(b.size());
         multMatrixByVector(tmp, a, r);
         cType beta = scalar(p, tmp) / scalar(p, p);
         for (int i = 0; i < z.size(); i++) {
            z[i] = r[i] + beta * z[i];
            p[i] = tmp[i] + beta * p[i];
         }
         disp = norm(r);
      }
   }
   void LOS::getResult(vector<cType>& res) {
      for (int i = 0; i < x.size(); i++) {
         res[i] = x[i];
      }
   }