//#include "SparseMatrix.h"
//
//double* SparseMatrix::selector(int i, int j)
//{
//   if (i == j) return &SparseMatrix::di[i];
//
//   if (i > j)
//   {
//      for (int ind = ig[i]; ind < ig[i + 1]; ind++)
//      {
//         if (jg[ind] == j)
//         {
//            return &SparseMatrix::gl[ind];
//         }
//      }
//   }
//
//   if (i < j)
//   {
//      for (int ind = ig[j]; ind < ig[j + 1]; ind++)
//      {
//         if (jg[ind] == i)
//         {
//            return &SparseMatrix::gu[ind];
//         }
//      }
//   }
//   return nullptr;
//
//}
//
//SparseMatrix::SparseMatrix()
//{
//}
//
//SparseMatrix::SparseMatrix(vector<int> ia, vector<int> ja, size_t size)
//{
//   SparseMatrix::ig = vector<int>(ia);
//   SparseMatrix::jg = vector<int>(ja);
//   SparseMatrix::di = vector<double>(size);
//   SparseMatrix::gu = vector<double>(SparseMatrix::jg.size());
//   SparseMatrix::gl = vector<double>(SparseMatrix::jg.size());
//}
//
//double SparseMatrix::getValue(int i, int j)
//{
//   auto result = SparseMatrix::selector(i, j);
//   return (result == nullptr) ? 0 : *result;
//}
//
//void SparseMatrix::setValue(int i, int j, double value)
//{
//   auto result = SparseMatrix::selector(i, j);
//   if (result != nullptr)
//      *(result) = value;
//}
//
//void SparseMatrix::addValue(int i, int j, double value)
//{
//   auto result = SparseMatrix::selector(i, j);
//   if (result != nullptr)
//      *(result) += value;
//}
//
//size_t SparseMatrix::size()
//{
//   return SparseMatrix::di.size();
//}
//
//vector<int> SparseMatrix::getColnsArray()
//{
//   return SparseMatrix::jg;
//}
//
//vector<int> SparseMatrix::getRowsArray()
//{
//   return SparseMatrix::ig;
//}
//void SparseMatrix::print(string filename)
//{
//   ofstream out(filename);
//   for (int i = 0; i < di.size(); i++)
//   {
//      for (int j = 0; j < di.size(); j++)
//      {
//         out << setprecision(5) << fixed << getValue(i, j) << " ";
//      }
//      out << endl;
//   }
//}
//
//void SparseMatrix::clear()
//{
//   for (int i = 0; i < SparseMatrix::di.size(); i++)
//      SparseMatrix::di[i] = 0;
//   for (int i = 0; i < SparseMatrix::gl.size(); i++)
//      SparseMatrix::gl[i] = 0;
//   for (int i = 0; i < SparseMatrix::gu.size(); i++)
//      SparseMatrix::gu[i] = 0;
//}
