#pragma once
#include <vector>
#include <memory>
#include "FEMSettings.h"

class Matrix {
protected:
   size_t _n;
public:
   Matrix() : _n(0) {}
   //virtual std::vector<cType>& operator[](size_t i) = 0;
   //virtual const std::vector<cType>& operator[](size_t i) const = 0;
   virtual cType& operator()(int i, int j) = 0;
   virtual const cType& operator()(int i, int j) const = 0;
   virtual std::shared_ptr<Matrix> operator+(const Matrix& a) const = 0;
   virtual std::shared_ptr<Matrix> operator-(const Matrix& a) const = 0;
   virtual std::shared_ptr<Matrix> operator+(const cType& a) const = 0;
   virtual std::shared_ptr<Matrix> operator-(const cType& a) const = 0;
   virtual std::shared_ptr<Matrix> operator*(const Matrix& a) const = 0;
   virtual std::shared_ptr<Matrix> operator*(const cType& a) const = 0;
   /*virtual std::shared_ptr<Matrix> friend operator+(const Matrix& a, cType value);
   std::shared_ptr<Matrix> friend operator+(cType value, const Matrix& a);
   std::shared_ptr<Matrix> friend operator-(const Matrix& a, cType value);
   std::shared_ptr<Matrix> friend operator-(cType value, const Matrix& a);
   std::shared_ptr<Matrix> friend operator*(const Matrix& a, cType value);
   std::shared_ptr<Matrix> friend operator*(cType value, const Matrix& a);*/
   const size_t getSize() const {
      return _n;
   }
};