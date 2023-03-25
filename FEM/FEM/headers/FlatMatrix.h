#pragma once
#include <vector>
#include "Matrix.h"
#include "FEMSettings.h"

class FlatMatrix : public Matrix {
   std::vector<std::vector<cType>> _mat;
public:
   FlatMatrix() : _mat({}) {
      _n = 0;
   }
   FlatMatrix(size_t n) : _mat(std::vector<std::vector<cType>>(n, std::vector<cType>(n, 0))) {
      _n = n;
   }
   FlatMatrix(std::vector<std::vector<cType>> mat) : _mat(mat) {
      _n = mat.size();
   }
   FlatMatrix(FlatMatrix& mat) {
      _n = mat._n;
      _mat = std::vector<std::vector<cType>>(_n, std::vector<cType>(_n, 0));
      for (size_t i{ 0 }; i < _n; i++) {
         for (size_t j{ 0 }; j < _n; j++) {
            _mat[i][j] = mat._mat[i][j];
         }
      }
   }
   FlatMatrix(Matrix& mat) {
      _n = mat.getSize();
      _mat = std::vector<std::vector<cType>>(_n, std::vector<cType>(_n, 0));
      for (size_t i{ 0 }; i < _n; i++) {
         for (size_t j{ 0 }; j < _n; j++) {
            _mat[i][j] = mat(i,j);
         }
      }
   }
   FlatMatrix(FlatMatrix&& mat) noexcept {
      _n = mat._n;
      _mat = std::move(mat._mat);
      mat._mat.clear();
      mat._n = 0;
   }
   FlatMatrix(size_t n, std::initializer_list<std::initializer_list<cType>> mat) {
      _n = n;
      for (const auto& item : mat) {
         _mat.push_back(std::vector<cType>(item));
      }
   }
   FlatMatrix& operator=(FlatMatrix& mat);
   FlatMatrix& operator=(FlatMatrix&& mat) noexcept;
   cType& operator()(int i, int j) override;
   const cType& operator()(int i, int j) const override;
   std::shared_ptr<Matrix> operator+(const Matrix& a) const override;
   std::shared_ptr<Matrix> operator-(const Matrix& a) const override;
   std::shared_ptr<Matrix> operator+(const cType& a) const override;
   std::shared_ptr<Matrix> operator-(const cType& a) const override;
   std::shared_ptr<Matrix> operator*(const Matrix& a) const override;
   std::shared_ptr<Matrix> operator*(const cType& a) const override;
   FlatMatrix friend operator*(const cType& value, const FlatMatrix& a);
   FlatMatrix friend operator*(const FlatMatrix& a, const cType& value);
};