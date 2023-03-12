#pragma once

#include <vector>
#include <string>
#include <memory>
#include "Mesh.h"
#include "Matrix.h"
#include "BoundaryCondition.h"


class LinearFEM {
   std::shared_ptr<Mesh> _mesh;
   std::shared_ptr<Matrix> _a;
   std::vector<cType> _b;
   std::vector<cType> _f;
   std::vector<cType> _solution;
   std::vector<std::shared_ptr<BoundaryCondition>> _firstBoundaries;
   std::vector<std::shared_ptr<BoundaryCondition>> _secondBoundaries;
   
   //Private Methods
   void AssemblyGlobalMatrix();
   void ConsiderFirstBoundary();
public:
   //Constructors
   LinearFEM() : _mesh({}), _a({}), _b({}), _solution({}) {}
   
   //Public Methods
   void CreateTask();
   void RunTask();
   void printSolution();
   
};