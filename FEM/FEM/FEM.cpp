#include <iostream>
#include <vector>
#include "headers/LinearFEM.h"
#include "headers/Matrix.h"

int main()
{
   try{
      LinearFEM fem;
      fem.CreateTask();
      fem.RunTask();
      fem.printSolution();
   }
   catch (std::exception& e) {
      std::cerr << e.what();
   }
   catch (std::string& str) {
      std::cerr << str;
   }
}