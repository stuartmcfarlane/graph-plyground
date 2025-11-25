#pragma once

#include "graph.h"
#include <Eigen/Dense>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;
using namespace graph;
using namespace Eigen;

namespace graph_algorithm {
  
  // https://en.wikipedia.org/wiki/Stress_majorization
  
  // template <typename W> bool iterate_smacof(vector<ArcXY<W>> &graph) {

  //   const int N = graph.size();
  //   MatrixX<W> X(N, 2);
  //   MatrixX<W> D(N, N);
  //   MatrixX<W> d(N, N);

  //   for (int i = 0; i < N; ++i) {
  //     const W xi = graph[i].x;
  //     const W yi = graph[i].y;
  //     X(i, 0) = xi;
  //     X(i, 1) = yi;
  //     D(i, i) = 0;
  //     d(i, i) = 0;
  //     for (int j = 0; j < i; ++j) {
  //       const W dx = graph[j].x - xi;
  //       const W dy = graph[j].y = yi;
  //       const W d = sqrt(dx*dx + dy*dy);
  //       D(i, j) = d;
  //       D(j, i) = d;
  //     }
  //   }

  //   cout << "X" << endl;
  //   cout << X << endl;
  //   cout << "D" << endl;
  //   cout << D << endl;
  //   return false;
  // }
  
}