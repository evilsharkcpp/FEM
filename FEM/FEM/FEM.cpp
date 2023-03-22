#include <iostream>
#include <vector>
#include "headers/LinearFEM.h"
#include "headers/Matrix.h"

int main()
{
   try{
      LinearFEM fem;
      fem.CreateTask();
      fem.RunTask("./l1.dat");
      //fem.printSolution();
      auto a = fem.getResult(Point3(+7.600000e-003, +1.300000e-003, 0));
      std::cout << std::scientific << a;
   }
   catch (std::exception& e) {
      std::cerr << e.what();
   }
   catch (std::string& str) {
      std::cerr << str;
   }
}