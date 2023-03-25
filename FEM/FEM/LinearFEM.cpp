#include "headers/LinearFEM.h"
#include "headers/LOS.h"
#include "headers/Element.h"
#include "headers/LineLinearElement.h"
#include <iostream>
#include <fstream>
#include <set>

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
void LinearFEM::ConsiderFirstBoundary(std::string fileName)
{
   std::ifstream in(fileName, ios::binary);
   int i = 0;
   while (!in.eof() && i++ < 105)
   {
      int a{};
      in.read((char*)&a, sizeof(a));
      //if (a >= _a->getSize()) continue;
      a--;
      for (int i{ 0 }; i < _a->getSize(); i++)
      {
         if (i != a)
            (*_a)(a,i) = 0;
         else
            (*_a)(a,i) = 1;
      }
      _b[a] = 0;
   }
}
void LinearFEM::makePortreit()
{
   auto vertCount = _mesh->getVertexes().size();
   vector<set<int>> list(vertCount);

   auto elems = _mesh->getElements();
   for (int i = 0; i < elems.size(); i++)
   {
      for (auto ind1 : elems[i]->getNodes())
      {
         for (auto ind2 : elems[i]->getNodes())
         {
            if (ind1 > ind2)
               list[ind1].insert(ind2);
         }
      }
   }
   vector<int> ig(vertCount + 1);
   vector<int> jg;
   vector<double> di;
   vector<double> gl;
   vector<double> gu;
   //создание портрета по списку
   ig[0] = ig[1] = 0;

   for (int i = 2; i < vertCount + 1; i++) {
      int col = ig[i - 1];
      ig[i] = col + list[i - 1].size();
   }
   jg.resize(ig[vertCount]);

   for (int i = 1, k = 0; i < vertCount; i++) {
      for (int j : list[i]) {
         jg[k] = j;
         k++;
      }
   }
   _a = shared_ptr<Matrix>(new SparseMatrix(ig, jg, vertCount));

}

void LinearFEM::CreateTask() {
   _mesh = std::shared_ptr<Mesh>(new Mesh());
   _mesh->readElements("./nvtr.dat", 1300);
   _mesh->readVertexes("./rz.dat", 1377);
   readMaterials("./toku", "./muk", "./nvkat2d.dat");
   makePortreit();
   //_mesh->buildMesh1(0, 2, 2, ElementType::LinearLine);
   //_a = std::shared_ptr<FlatMatrix>(new FlatMatrix(_mesh->getVertexes().size()));
   _b = std::vector<cType>(_mesh->getVertexes().size());
   //_f = std::vector<cType>(_mesh->getVertexes().size());
   _solution = std::vector<cType>(_mesh->getVertexes().size());
   //_firstBoundaries.push_back(std::shared_ptr<BoundaryCondition>(new BoundaryCondition(0, { 0 }, { 0, 0 })));
   //_firstBoundaries.push_back(std::shared_ptr<BoundaryCondition>(new BoundaryCondition(_mesh->getElements().size() - 1, { 1 }, { 0, _mesh->getVertexes().back()->x })));
}

void LinearFEM::RunTask(std::string fname) {
   AssemblyGlobalMatrix();
   if (fname == "")
      ConsiderFirstBoundary();
   else
      ConsiderFirstBoundary(fname);
   auto los = new LOS(_a, _b, 50000);
   auto start = std::vector<cType>(_b.size(), 0);
   //los->calculate(start);
   los->calculateFast(start);
   los->getResult(_solution);
}

void LinearFEM::printSolution()
{
   for (auto& element : _solution)
      std::cout << element << "\n";
}

void LinearFEM::readMaterials(std::string fileTok, std::string fileMu, std::string fileMaterials)
{
   std::ifstream in(fileTok);
   int a{};
   double b{};
   double pi = 3.14159265;
   double mu0 = 4 * pi * 1e-7;

   std::vector<double> tok;
   while (in >> a >> b)
   {
      tok.push_back(b);
   }
   in.close();
   in.open(fileMu);
   std::vector<double> mu;//{ 1,1000,1,1 };
   while (in >> a >> b)
   {
      mu.push_back(1.0 / (b * mu0));
   }
   in.close();
   in.open(fileMaterials, ios::binary);
   size_t size = this->_mesh->getElements().size();
   auto elem = this->_mesh->getElements();
   _f = std::vector<cType>(this->_mesh->getVertexes().size());
   for (int i{ 0 }; i < size; i++)
   {
      int c{};
      in.read((char*)&c, sizeof(c));
      elem[i]->setLambda(mu[c - 1]);
      auto nodes = elem[i]->getNodes();
      for (const auto& item : nodes)
      {
         _f[item] = tok[c - 1];
      }
   }
}

double LinearFEM::getResult(Point3 value)
{
   auto elem = _mesh->getElements();
   auto vert = _mesh->getVertexes();
   for (auto& item : elem)
   {
      if (item->isInside(value, vert))
      {
         double f1, f2, f3, f4;
         double q1, q2, q3, q4;
         double x1, x2, y1, y2;
         double hx = vert[item->getNodes()[3]]->x - vert[item->getNodes()[0]]->x;
         double hy = vert[item->getNodes()[3]]->y - vert[item->getNodes()[0]]->y;
         x1 = (vert[item->getNodes()[3]]->x - value.x) / hx;
         y1 = (vert[item->getNodes()[3]]->y - value.y) / hy;
         x2 = (value.x - vert[item->getNodes()[0]]->x) / hx;
         y2 = (value.y - vert[item->getNodes()[0]]->y) / hy;

         f1 = x1 * y1;
         f2 = x2 * y1;
         f3 = x1 * y2;
         f4 = x2 * y2;

         q1 = _solution[item->getNodes()[0]];
         q2 = _solution[item->getNodes()[1]];
         q3 = _solution[item->getNodes()[2]];
         q4 = _solution[item->getNodes()[3]];

         double v = q1 * f1 + q2 * f2 + q3 * f3 + q4 * f4;
         return v;

      }
   }
}

double LinearFEM::getB(Point3 value)
{
   auto elem = _mesh->getElements();
   auto vert = _mesh->getVertexes();
   for (auto& item : elem)
   {
      if (item->isInside(value, vert))
      {
         double f1_dx, f2_dx, f3_dx, f4_dx;
         double f1_dy, f2_dy, f3_dy, f4_dy;
         double q1, q2, q3, q4;

         double hx = vert[item->getNodes()[3]]->x - vert[item->getNodes()[0]]->x;
         double hy = vert[item->getNodes()[3]]->y - vert[item->getNodes()[0]]->y;

         f1_dx = (value.y - vert[item->getNodes()[3]]->y) / (hx * hy);
         f2_dx = (vert[item->getNodes()[3]]->y - value.y) / (hx * hy);
         f3_dx = (vert[item->getNodes()[0]]->y - value.y) / (hx * hy);
         f4_dx = (value.y - vert[item->getNodes()[0]]->y) / (hx * hy);

         f1_dy = (value.x - vert[item->getNodes()[3]]->x) / (hx * hy);
         f2_dy = (vert[item->getNodes()[0]]->x - value.x) / (hx * hy);
         f3_dy = (vert[item->getNodes()[3]]->x - value.x) / (hx * hy);
         f4_dy = (value.x - vert[item->getNodes()[0]]->x) / (hx * hy);

         q1 = _solution[item->getNodes()[0]];
         q2 = _solution[item->getNodes()[1]];
         q3 = _solution[item->getNodes()[2]];
         q4 = _solution[item->getNodes()[3]];

         double B_dx = q1 * f1_dx + q2 * f2_dx + q3 * f3_dx + q4 * f4_dx;
         double B_dy = q1 * f1_dy + q2 * f2_dy + q3 * f3_dy + q4 * f4_dy;
         double B = sqrt(B_dx * B_dx + B_dy * B_dy);
         return B;


      }
   }
}
