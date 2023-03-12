#pragma once
#include "FEMSettings.h"
class BoundaryCondition {
public:
   size_t elementIndex;
   std::vector<size_t> localValueIndexes;
   std::vector<cType> value;
   BoundaryCondition() : BoundaryCondition(0, {}, {}) {}
   BoundaryCondition(size_t index, std::vector<size_t> localValueIndexes, std::vector<cType> val) : elementIndex(index), localValueIndexes(localValueIndexes), value(val) {}
};