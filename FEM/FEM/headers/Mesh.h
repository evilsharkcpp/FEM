#pragma once
#include <vector>
#include <string>
#include <memory>
#include "RectangleLinearElement.h"
#include "LineLinearElement.h"
#include "Point3.h"
#include "Element.h"

class Mesh {
   std::vector<std::shared_ptr<Point3>> _vertexes;
   std::vector<std::shared_ptr<Element>> _elements;
public:
   const decltype(_vertexes) getVertexes() { return _vertexes; }
   const decltype(_elements) getElements() { return _elements; }
   Mesh() : _vertexes({}), _elements({}) {}

   //Methods
   void buildMesh1(cType a, cType b, size_t splitCount, ElementType type);
};