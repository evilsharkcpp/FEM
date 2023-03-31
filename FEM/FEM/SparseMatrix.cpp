#include "SparseMatrix.h"
#include <fstream>
#include <iomanip>
using namespace std;

double* SparseMatrix::selector(int i, int j)
{
   if (i == j) return &SparseMatrix::di[i];

   if (i > j)
   {
      for (int ind = ig[i]; ind < ig[i + 1]; ind++)
      {
         if (jg[ind] == j)
         {
            return &SparseMatrix::gl[ind];
         }
      }
   }

   if (i < j)
   {
      for (int ind = ig[j]; ind < ig[j + 1]; ind++)
      {
         if (jg[ind] == i)
         {
            return &SparseMatrix::gu[ind];
         }
      }
   }
   return nullptr;

}

SparseMatrix::SparseMatrix()
{
}

SparseMatrix::SparseMatrix(vector<int> ia, vector<int> ja, size_t size)
{
   SparseMatrix::ig = vector<int>(ia);
   SparseMatrix::jg = vector<int>(ja);
   SparseMatrix::di = vector<double>(size);
   SparseMatrix::gu = vector<double>(SparseMatrix::jg.size());
   SparseMatrix::gl = vector<double>(SparseMatrix::jg.size());
   _n = size;
}

double SparseMatrix::getValue(int i, int j)
{
   auto result = SparseMatrix::selector(i, j);
   return (result == nullptr) ? 0 : *result;
}

void SparseMatrix::setValue(int i, int j, double value)
{
   auto result = SparseMatrix::selector(i, j);
   if (result != nullptr)
      *(result) = value;
}

void SparseMatrix::addValue(int i, int j, double value)
{
   auto result = SparseMatrix::selector(i, j);
   if (result != nullptr)
      *(result) += value;
}

size_t SparseMatrix::size()
{
   return SparseMatrix::di.size();
}

cType& SparseMatrix::operator()(int i, int j)
{
   if (i == j) return SparseMatrix::di[i];

   if (i > j)
   {
      for (int ind = ig[i]; ind < ig[i + 1]; ind++)
      {
         if (jg[ind] == j)
         {
            return SparseMatrix::gl[ind];
         }
      }
   }

   if (i < j)
   {
      for (int ind = ig[j]; ind < ig[j + 1]; ind++)
      {
         if (jg[ind] == i)
         {
            return SparseMatrix::gu[ind];
         }
      }
   }
   double nul = 0;
   return nul;
}

const cType& SparseMatrix::operator()(int i, int j) const
{
   if (i == j) return SparseMatrix::di[i];

   if (i > j)
   {
      for (int ind = ig[i]; ind < ig[i + 1]; ind++)
      {
         if (jg[ind] == j)
         {
            return SparseMatrix::gl[ind];
         }
      }
   }

   if (i < j)
   {
      for (int ind = ig[j]; ind < ig[j + 1]; ind++)
      {
         if (jg[ind] == i)
         {
            return SparseMatrix::gu[ind];
         }
      }
   }
   double nul = 0;
   return nul;
}

vector<int> SparseMatrix::getColnsArray()
{
   return SparseMatrix::jg;
}

vector<int> SparseMatrix::getRowsArray()
{
   return SparseMatrix::ig;
}
void SparseMatrix::print(string filename)
{
   ofstream out(filename);
   for (int i = 0; i < di.size(); i++)
   {
      for (int j = 0; j < di.size(); j++)
      {
         out << setprecision(5) << fixed << getValue(i, j) << " ";
      }
      out << endl;
   }
}

void SparseMatrix::clear()
{
   for (int i = 0; i < SparseMatrix::di.size(); i++)
      SparseMatrix::di[i] = 0;
   for (int i = 0; i < SparseMatrix::gl.size(); i++)
      SparseMatrix::gl[i] = 0;
   for (int i = 0; i < SparseMatrix::gu.size(); i++)
      SparseMatrix::gu[i] = 0;
}

std::shared_ptr<Matrix> SparseMatrix::operator+(const Matrix& a) const
{
   auto res = std::shared_ptr<Matrix>(new SparseMatrix(this));
   for (int i = 0; i < a.getSize(); i++)
      for (int j = 0; j < a.getSize(); j++)
        (*res)(i, j) = (*res)(i, j) + a(i, j);
   return res;
}
std::shared_ptr<Matrix> SparseMatrix::operator-(const Matrix& a) const
{
   auto res = std::shared_ptr<Matrix>(new SparseMatrix(this));
   for (int i = 0; i < a.getSize(); i++)
      for (int j = 0; j < a.getSize(); j++)
         (*res)(i, j) = (*res)(i, j) - a(i, j);
   return res;
}
std::shared_ptr<Matrix> SparseMatrix::operator+(const cType& a) const
{
   auto res = std::shared_ptr<Matrix>(new SparseMatrix(this));
   for (int i = 0; i < _n; i++)
      (*res)(i, i) = (*res)(i, i) + a;
   return res;
}
std::shared_ptr<Matrix> SparseMatrix::operator-(const cType& a) const
{
   return operator+(-a);
}
std::shared_ptr<Matrix> SparseMatrix::operator*(const Matrix& a) const
{
   auto result = std::shared_ptr<Matrix>(new SparseMatrix(this));
   for (size_t i{ 0 }; i < _n; i++) {
      for (size_t j{ 0 }; j < _n; j++) {
         double res{};
         for (size_t k{ 0 }; k < _n; k++) {
            res += (*result)(i, k) * a(k, j);
         }
         (*result)(i, j) = res;
      }
   }
   return result;
}
std::shared_ptr<Matrix> SparseMatrix::operator*(const cType& a) const
{
   auto res = std::shared_ptr<Matrix>(new SparseMatrix(this));
   for (int i = 0; i < _n; i++)
      for (int j = 0; j < _n; j++)
      (*res)(i, j) = (*res)(i, j) * a;
   return res;
}
