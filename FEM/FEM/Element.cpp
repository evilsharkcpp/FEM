#include "headers/Element.h"

void Element::ConsiderFirstBoundary(std::shared_ptr<Matrix>& matrix, std::vector<cType>& b, const std::shared_ptr<BoundaryCondition>& boundary) {
   for (auto& node : boundary->localValueIndexes) {
      for (size_t i{ 0 }; i < matrix->getSize(); i++) {
         if (i != _nodes[node]) {
            (*matrix)[_nodes[node]][i] = 0;
         }
         else {
            (*matrix)[_nodes[node]][i] = 1;
         }
      }
      b[_nodes[node]] = boundary->value[node];
   }
}