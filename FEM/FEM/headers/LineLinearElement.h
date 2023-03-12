#pragma once
#include "Element.h"
#include "FlatMatrix.h"
#include <vector>
#include <memory>
#include "Matrix.h"

class LineLinearElement : public Element {
public:
   LineLinearElement() : Element::Element(ElementType::LinearLine, {}, 1, 0) {}
   LineLinearElement(std::vector<size_t> nodes) : Element::Element(ElementType::LinearLine, nodes, 1, 0) {}
   void addToGlobal(std::shared_ptr<Matrix>& matrix, std::vector<cType>& b,
      const std::vector<std::shared_ptr<Point3>>& vertexes, const std::vector<cType> f) override;

};