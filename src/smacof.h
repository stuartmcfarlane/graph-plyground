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
    WeightType δOf(const Graph<NodeKeyType, WeightType> &graph, const NodeKeyType& from, const NodeKeyType& to) {
      return graph.weightOf(from, to, INFINITY);
    }

    template <typename WeightType>
    WeightType ωOf(WeightType δ) {
      const WeightType α = 2;
      return pow(δ, -α);
    }

    template <typename NodeKeyType, typename WeightType>
    
    bool iterate_smacof(map<NodeKeyType, Point> points,
      const Graph<NodeKeyType, WeightType> &graph) {
        
        const int N = points.size();
        
        MatrixX<float> X(N, 2);
        MatrixX<float> D(N, N);
        MatrixX<float> δ(N, N);
        MatrixX<float> ω(N, N);
        
        vector<NodeKeyType> nodeByIndex;
        for (auto nodePoint : points) {
          nodeByIndex.push_back(nodePoint.first);
        }
        
        for (size_t i = 0; i < N; ++i) {
          auto iNode = nodeByIndex[i];
          auto [xi, yi] = points[iNode];
          X(i, 0) = xi;
          X(i, 1) = yi;
          D(i, i) = 0;
          δ(i, i) = δOf(graph, iNode, iNode);
          ω(i, i) = ωOf(δ(i, i));
          for (int j = 0; j < i; ++j) {
            auto jNode = nodeByIndex[j];
            auto [xj, yj] = points[jNode];
            const float dx = xj - xi;
            const float dy = yj = yi;
            const float d = sqrt(dx * dx + dy * dy);
            D(i, j) = d;
            D(j, i) = d;
            δ(i, j) = δOf(graph, iNode, jNode);
            δ(j, i) = δOf(graph, jNode, iNode);
            ω(i, j) = ωOf(δ(i, j));
            ω(j, i) = ωOf(δ(j, i));
          }
        }
        auto transposeX = X.transpose();
        
        cout << "X" << endl;
        cout << X << endl;
        cout << "transposeX" << endl;
        cout << transposeX << endl;
        cout << "D" << endl;
        cout << D << endl;
        cout << "δ" << endl;
        cout << δ << endl;
        cout << "ω" << endl;
        cout << ω << endl;
        
        return false;
      }
    }
    