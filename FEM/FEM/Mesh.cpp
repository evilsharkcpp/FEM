#include "headers/Mesh.h"
#include "fstream"
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

void Mesh::readVertexes(std::string fileName, int vertexesCount)
{
   std::ifstream in(fileName, std::ios_base::binary);
   for (int i{ 0 }; i < vertexesCount; i++)
   {
      double x{}, y{};
      in.read((char*)&x, sizeof(x));
      in.read((char*)&y, sizeof(y));
      this->_vertexes.push_back(std::shared_ptr<Point3>(new Point3(x, y, 0)));
   }
   in.close();
}

void Mesh::readElements(std::string fileName, int elementsCount)
{
   std::ifstream in(fileName, std::ios_base::binary);
   for (int i{ 0 }; i < elementsCount; i++)
   {
      std::vector<size_t> nodes;
      size_t a{};
      for (int k = 0; k < 4; k++)
      {
         in.read((char*)&a, sizeof(int));
         nodes.push_back(a - 1);
      }
      std::vector<size_t> nodes1{ nodes[2], nodes[3], nodes[0], nodes[1] };
      in.read((char*)&a, sizeof(int));
      in.read((char*)&a, sizeof(int));
      //in.read((char*)&nodes, 4*sizeof(nodes));
      this->_elements.push_back(std::shared_ptr<Element>(new RectangleLinearElement(nodes1)));
      
   }
   in.close();
}
