﻿#include <iostream>
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
      //fem.printSolution();
      std::ofstream out("out.txt");
      std::vector<Point3> points = std::vector<Point3>{ Point3(-0.011,0.001,0), Point3(-0.0019,0.0008,0), Point3(-0.0009,0.0002,0), Point3(0.0024,0.0008,0), Point3(0.0076,0.0013,0) };
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