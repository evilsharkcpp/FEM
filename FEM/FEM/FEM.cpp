#include <iostream>
#include <vector>
#include "headers/LinearFEM.h"
#include "headers/Matrix.h"
#include <fstream>
int main()
{
   try{
      LinearFEM fem;
      fem.CreateTask();
      fem.RunTask("./l1.dat");
      fem.printSolution();
      std::ofstream out("out.txt");
      std::vector<Point3> points = std::vector<Point3>{ Point3(-4.20000E-03 ,3.00000E-03,0) };
      for (auto& p : points)
      {
         auto a = fem.getResult(p);
         auto B = fem.getB(p);
         
         out << std::scientific << a << "\n" << B <<"\n\n";
      }
      
   }
   catch (std::exception& e) {
      std::cerr << e.what();
   }
   catch (std::string& str) {
      std::cerr << str;
   }
}