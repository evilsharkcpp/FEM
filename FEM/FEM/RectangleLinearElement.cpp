#include "headers/RectangleLinearElement.h"
#include "headers/FlatMatrix.h"

void RectangleLinearElement::addToGlobal(std::shared_ptr<Matrix>& matrix, std::vector<cType>& b, const std::vector<std::shared_ptr<Point3>>& vertexes, const std::vector<cType> f)
{
   auto gx = FlatMatrix(4,
      {
        { 2, -2, 1, -1 },
        { -2, 2, -1, 1 },
        { 1, -1, 2, -2 },
        { -1, 1, -2, 2 },
      });
   auto gy = FlatMatrix(4,
      {
        { 2, 1, -2, -1 },
        { 1, 2, -1, -2 },
        { -2, -1, 2, 1 },
        { -1, -2, 1, 2 },
      });
   auto m = FlatMatrix(4,
      {
         { 4, 2, 2, 1 },
         { 2, 4, 1, 2 },
         { 2, 1, 4, 2 },
         { 1, 2, 2, 4 },
      });
   cType hx = vertexes[this->_nodes[1]]->x - vertexes[this->_nodes[0]]->x;
   cType hy = vertexes[this->_nodes[2]]->y - vertexes[this->_nodes[0]]->y;
   auto localA = *((this->_lambda * hy / (6 * hx)) * gx + (this->_lambda * hx / (6 * hy)) * gy) + this->_gamma * hx * hy / 36 * m;
   auto localB = hx * hy / 36 * m;
   for (size_t i{ 0 }; i < this->_nodes.size(); i++) {
      for (size_t j{ 0 }; j < this->_nodes.size(); j++) {
         (*matrix)[this->_nodes[i]][this->_nodes[j]] += (*localA)[i][j];
         b[this->_nodes[i]] += f[this->_nodes[i]] * localB[i][j];
      }
   }
}
