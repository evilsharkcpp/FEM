#include <iostream>
#include <vector>
#include "headers/LinearFEM.h"
#include "headers/Matrix.h"

//template<class T>
//class Matrix {
//   size_t _n;
//   std::vector<std::vector<T>> _mat;
//public:
//   Matrix() : _n(0), _mat({}) {}
//   Matrix(size_t n) : _n(n), _mat(std::vector<std::vector<T>>(n, std::vector<T>(n, 0))) {}
//   Matrix(Matrix& mat) {
//      _n = mat._n;
//      _mat = std::vector<std::vector<T>>(_n, std::vector<T>(_n, 0));
//      for (size_t i{ 0 }; i < _n; i++) {
//         for (size_t j{ 0 }; j < _n; j++) {
//            _mat[i][j] = mat._mat[i][j];
//         }
//      }
//   }
//   Matrix(Matrix&& mat) noexcept {
//      _n = mat._n;
//      _mat = std::move(mat._mat);
//      mat._mat.clear();
//      mat._n = 0;
//   }
//
//   //operators
//   Matrix& operator=(Matrix& mat) {
//      _n = mat._n;
//      _mat = std::vector<std::vector<T>>(_n, std::vector<T>(_n, 0));
//      for (size_t i{ 0 }; i < _n; i++) {
//         for (size_t j{ 0 }; j < _n; j++) {
//            _mat[i][j] = mat._mat[i][j];
//         }
//      }
//      return this;
//   }
//   Matrix& operator=(Matrix&& mat) {
//      _n = mat._n;
//      _mat = std::move(mat._mat);
//      mat._mat.clear();
//      mat._n = 0;
//      return this;
//   }
//   std::vector<T>& operator[](size_t i) {
//      return _mat[i];
//   }
//
//   //Math operators
//   Matrix operator+(const Matrix& a) {
//      Matrix result(a._n);
//      for (size_t i{ 0 }; i < _n; i++) {
//         for (size_t j{ 0 }; j < _n; j++) {
//            result._mat[i][j] = _mat[i][j] + a._mat[i][j];
//         }
//      }
//      return result;
//   }
//   Matrix operator-(const Matrix& a) {
//      Matrix result(a._n);
//      for (size_t i{ 0 }; i < _n; i++) {
//         for (size_t j{ 0 }; j < _n; j++) {
//            result._mat[i][j] = _mat[i][j] - a._mat[i][j];
//         }
//      }
//      return result;
//   }
//   Matrix friend operator*(const T& value, const Matrix& a) {
//      Matrix result(a._n);
//      for (size_t i{ 0 }; i < a._n; i++) {
//         for (size_t j{ 0 }; j < a._n; j++) {
//            result._mat[i][j] = value * a._mat[i][j];
//         }
//      }
//      return result;
//
//   }
//   Matrix friend operator*(const Matrix& a, const T& value) {
//      return operator*(value, a);
//   }
//};

int main()
{
   try{
      LinearFEM fem;
      fem.CreateTask();
      fem.RunTask();
      fem.printSolution();
   }
   catch (std::exception& e) {
      std::cerr << e.what();
   }
   catch (std::string& str) {
      std::cerr << str;
   }
}