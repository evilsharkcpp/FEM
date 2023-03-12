#pragma once
#include <vector>
#include <memory>
#include "Point3.h"
#include "Matrix.h"
#include "BoundaryCondition.h"
#include "FEMSettings.h"

enum class ElementType {
   None,
   LinearRectangle,
   LinearLine,
};

class Element {
protected:
   ElementType _type;
   std::vector<size_t> _nodes;
   cType _lambda;
   cType _gamma;
public:
   Element() : _type(ElementType::None), _nodes({}), _lambda(0), _gamma(0) {}
   Element(ElementType type, std::vector<size_t> nodes, cType lambda, cType gamma) :
      _type(type), _nodes(std::vector<size_t>(nodes)), _lambda(lambda), _gamma(gamma) {}
   virtual void addToGlobal(std::shared_ptr<Matrix>& matrix, std::vector<cType>& b, const std::vector<std::shared_ptr<Point3>>& vertexes, const std::vector<cType> f) = 0;
   virtual void ConsiderFirstBoundary(std::shared_ptr<Matrix>& matrix, std::vector<cType>& b, const std::shared_ptr<BoundaryCondition>& boundary);
};