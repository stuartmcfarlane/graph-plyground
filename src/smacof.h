#pragma once

#include "graph.h"
#include <Eigen/Dense>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <vector>

using namespace std;
using namespace graph;
using namespace Eigen;

namespace graph_algorithm {
  
  struct Point {
    float x;
    float y;
  };

  inline std::ostream &operator<<(std::ostream &os,
                           Point const &point) {
    os << "(" << point.x << "," << point.y << ")";
    return os;
  }

  // https://en.wikipedia.org/wiki/Stress_majorization

  template <typename NodeKeyType, typename WeightType>
  
  bool iterate_smacof(map<NodeKeyType, Point> points,  Adjacent<NodeKeyType, WeightType> &adjacent) {

    cout << "points: [";
    for (auto [n, p] : points) {
      cout << n << ":" << p << ", ";
    }
    cout << "]" << endl;
    const int N = points.size();
    cout << "N: " << N << endl;
    vector<NodeKeyType> nodeByIndex;
    MatrixX<float> X(N, 2);
    MatrixX<float> D(N, N);
    MatrixX<float> d(N, N);

    for (auto nodePoint : points) {
      nodeByIndex.push_back(nodePoint.first);
    }
    for (size_t i = 0; i < N; ++i) {
        auto [xi, yi] = points[nodeByIndex[i]];
        X(i, 0) = xi;
        X(i, 1) = yi;
        D(i, i) = 0;
        d(i, i) = 0;
        for (int j = 0; j < i; ++j) {
          auto [xj, yj] = points[nodeByIndex[j]];
          const float dx = xj - xi;
          const float dy = yj = yi;
          const float d = sqrt(dx * dx + dy * dy);
          D(i, j) = d;
          D(j, i) = d;
        }
      }

      cout << "X" << endl;
      cout << X << endl;
      cout << "D" << endl;
      cout << D << endl;
      return false;
    }
}