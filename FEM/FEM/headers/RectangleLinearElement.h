#pragma once
#include "Element.h"
#include <vector>
#include "Point3.h"
#include "Matrix.h"
#include <memory>

class RectangleLinearElement : public Element {
public:
   RectangleLinearElement() : Element::Element(ElementType::LinearRectangle, {}, 0, 0) {}
   RectangleLinearElement(std::vector<size_t> nodes) : Element::Element(ElementType::LinearRectangle, nodes, 0, 0) {}
   void addToGlobal(std::shared_ptr<Matrix>& matrix, std::vector<cType>& b, const std::vector<std::shared_ptr<Point3>>& vertexes, const std::vector<cType> f) override;
};