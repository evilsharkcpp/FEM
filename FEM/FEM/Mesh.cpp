#include "headers/Mesh.h"

void Mesh::buildMesh1(cType a, cType b, size_t splitCount, ElementType type) {
   cType h = (b - a) / splitCount;
   _vertexes.push_back(std::make_shared<Point3>(a, 0, 0));
   for (size_t i{ 1 }; i <= splitCount; i++) {
      _vertexes.push_back(std::make_shared<Point3>(a + h * i, 0, 0));
      switch (type)
      {
      case ElementType::LinearRectangle:
         _elements.push_back(std::make_shared<RectangleLinearElement>());
         break;
      case ElementType::LinearLine:
         _elements.push_back(std::shared_ptr<LineLinearElement>(new LineLinearElement({ i - size_t(1), i })));
         break;
      default:
         throw std::string("Unknown element type or none");
         break;
      }
   }
}