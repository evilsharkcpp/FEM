#include "headers/LinearFEM.h"
#include "headers/LOS.h"
#include "headers/Element.h"
#include "headers/LineLinearElement.h"
#include <iostream>

void LinearFEM::AssemblyGlobalMatrix() {
   try {
      auto a = std::shared_ptr<FlatMatrix>(new FlatMatrix(2, { {1,2},{3,4}, }));
      if (!_mesh.operator bool())
         throw std::string("Mesh is null");
      for (const auto& element : _mesh->getElements()) {
         element->addToGlobal(_a, _b, _mesh->getVertexes(), _f);
      }

   }
   catch (...) {
      throw;
   }
}
void LinearFEM::ConsiderFirstBoundary() {
   for (auto& boundary : _firstBoundaries) {
      auto element = _mesh->getElements()[boundary->elementIndex];
      element->ConsiderFirstBoundary(_a, _b, boundary);
   }
}
void LinearFEM::CreateTask() {
   _mesh = std::shared_ptr<Mesh>(new Mesh());
   _mesh->buildMesh1(0, 2, 2, ElementType::LinearLine);
   _a = std::shared_ptr<FlatMatrix>(new FlatMatrix(_mesh->getVertexes().size()));
   _b = std::vector<cType>(_mesh->getVertexes().size());
   _f = std::vector<cType>(_mesh->getVertexes().size());
   _solution = std::vector<cType>(_mesh->getVertexes().size());
   _firstBoundaries.push_back(std::shared_ptr<BoundaryCondition>(new BoundaryCondition(0, { 0 }, { 0, 0 })));
   _firstBoundaries.push_back(std::shared_ptr<BoundaryCondition>(new BoundaryCondition(_mesh->getElements().size() - 1, { 1 }, { 0, _mesh->getVertexes().back()->x })));
}
void LinearFEM::RunTask() {
   AssemblyGlobalMatrix();
   ConsiderFirstBoundary();
   auto los = new LOS(_a, _b, 10000);
   auto start = std::vector<cType>(_b.size(), 0);
   los->calculate(start);
   los->getResult(_solution);
}

void LinearFEM::printSolution()
{
   for (auto& element : _solution)
      std::cout << element << "\n";
}
