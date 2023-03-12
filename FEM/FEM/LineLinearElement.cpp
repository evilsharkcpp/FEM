#include "headers/LineLinearElement.h"

void LineLinearElement::addToGlobal(std::shared_ptr<Matrix>& matrix, std::vector<cType>& b, const std::vector<std::shared_ptr<Point3>>& vertexes, const std::vector<cType> f) {
   auto g = FlatMatrix(2,
      {
        { 1, -1 },
        { -1, 1 },
      });
   auto m = FlatMatrix(2,
      {
         { 2, 1 },
         { 1, 2 },
      });
   cType h = vertexes[this->_nodes[1]]->x - vertexes[this->_nodes[0]]->x;
   auto localA = this->_lambda / (2 * h) * g + this->_gamma * h / 6 * m;
   auto localB = h / 6 * m;
   for (size_t i{ 0 }; i < this->_nodes.size(); i++) {
      for (size_t j{ 0 }; j < this->_nodes.size(); j++) {
         (*matrix)[this->_nodes[i]][this->_nodes[j]] += (*localA)[i][j];
         b[this->_nodes[i]] += f[this->_nodes[i]] * localB[i][j];
      }
   }
}