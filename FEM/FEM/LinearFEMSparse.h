#pragma once

#include <vector>
#include <string>
#include <memory>
#include "headers/Mesh.h"
#include "SparseMatrix.h"
#include "headers/LinearFEM.h"
#include "headers/BoundaryCondition.h"


class LinearFEMSparse : LinearFEM {
   std::shared_ptr<Mesh> _mesh;
   std::shared_ptr<SparseMatrix> _a;
   std::vector<cType> _b;
   std::vector<cType> _f;
   std::vector<cType> _solution;
   std::vector<std::shared_ptr<BoundaryCondition>> _firstBoundaries;
   std::vector<std::shared_ptr<BoundaryCondition>> _secondBoundaries;

   //Private Methods
   void AssemblyGlobalMatrix();
   void ConsiderFirstBoundary();
   void ConsiderFirstBoundary(std::string fileName);
public:
   //Constructors
   LinearFEMSparse() : _mesh({}), _a({}), _b({}), _solution({}) {}

   //Public Methods
   void CreateTask();
   void RunTask(std::string fname = "");
   void printSolution();
   void readMaterials(std::string fileTok, std::string fileMu, std::string fileMaterials);
   double getResult(Point3 value);
};