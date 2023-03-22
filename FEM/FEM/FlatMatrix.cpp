#include "headers/FlatMatrix.h"

//operators
FlatMatrix& FlatMatrix::operator=(FlatMatrix& mat) {
   _n = mat._n;
   _mat = std::vector<std::vector<cType>>(_n, std::vector<cType>(_n, 0));
   for (size_t i{ 0 }; i < _n; i++) {
      for (size_t j{ 0 }; j < _n; j++) {
         _mat[i][j] = mat._mat[i][j];
      }
   }
   return *this;
}
FlatMatrix& FlatMatrix::operator=(FlatMatrix&& mat) noexcept {
   _n = mat._n;
   _mat = std::move(mat._mat);
   mat._mat.clear();
   mat._n = 0;
   return *this;
}
std::vector<cType>& FlatMatrix::operator[](size_t i) {
   return _mat[i];
}
const std::vector<cType>& FlatMatrix::operator[](size_t i) const {
   return _mat[i];
}

//Math operators
std::shared_ptr<Matrix> FlatMatrix::operator+(const Matrix& a) const {
   auto result = std::shared_ptr<Matrix>(new FlatMatrix(a.getSize()));
   for (size_t i{ 0 }; i < _n; i++) {
      for (size_t j{ 0 }; j < _n; j++) {
         (*result)[i][j] = _mat[i][j] + a[i][j];
      }
   }
   return result;
}
std::shared_ptr<Matrix> FlatMatrix::operator-(const Matrix& a) const {
   auto result = std::shared_ptr<Matrix>(new FlatMatrix(a.getSize()));
   for (size_t i{ 0 }; i < _n; i++) {
      for (size_t j{ 0 }; j < _n; j++) {
         (*result)[i][j] = _mat[i][j] - a[i][j];
      }
   }
   return result;
}
std::shared_ptr<Matrix> FlatMatrix::operator+(const cType& a) const
{
   auto result = std::shared_ptr<Matrix>(new FlatMatrix(this->_mat));
   for (size_t i{ 0 }; i < _n; i++) {
      (*result)[i][i] = _mat[i][i] + a;
   }
   return result;
}
std::shared_ptr<Matrix> FlatMatrix::operator-(const cType& a) const
{
   return operator+(-a);
}
std::shared_ptr<Matrix> FlatMatrix::operator*(const Matrix& a) const
{
   auto result = std::shared_ptr<Matrix>(new FlatMatrix(a.getSize()));
   for (size_t i{ 0 }; i < _n; i++) {
      for (size_t j{ 0 }; j < _n; j++) {
         (*result)[i][j] += a[i][j] * _mat[j][i];
      }
   }
   return result;
}
std::shared_ptr<Matrix> FlatMatrix::operator*(const cType& a) const
{
   auto result = std::shared_ptr<Matrix>(new FlatMatrix(this->_mat));
   for (size_t i{ 0 }; i < _n; i++) {
      for (size_t j{ 0 }; j < _n; j++)
      (*result)[i][j] = _mat[i][j] * a;
   }
   return result;
}
FlatMatrix operator*(const cType& value, const FlatMatrix& a) {
   FlatMatrix result(a.getSize());
   for (size_t i{ 0 }; i < a.getSize(); i++) {
      for (size_t j{ 0 }; j < a.getSize(); j++) {
         result[i][j] = value * a[i][j];
      }
   }
   return result;
}
FlatMatrix operator*(const FlatMatrix& a, const cType& value) {
   return operator*(value, a);
}