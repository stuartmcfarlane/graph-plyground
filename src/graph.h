#pragma once

#include <map>
#include <set>
#include <sstream>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

namespace graph {

template <typename N> struct NodeXY {
  N name;
  float x;
  float y;
};

template <typename N, typename W = float>
using Arc = std::tuple<N, N, W>;

template <typename N, typename W = float>
using Adjacent = std::map<N, std::map<N, W>>;

template <typename N, typename W> struct Graph {
  std::set<N> nodes;
  std::vector<Arc<N, W>> arcs;
  Adjacent<N, W> adjacent;
};

template <typename W>
Graph<std::string, W> lines2graph(std::vector<std::string> const &lines) {
  Graph<std::string, W> graph;
  for (auto line : lines) {
    std::string a, b;
    W w;
    std::stringstream ss(line);
    ss >> a;
    ss >> b;
    ss >> w;
    if (graph.nodes.contains(a)) {
      graph.nodes.insert(a);
    }
    graph.arcs.push_back(Arc<std::string, W>(a, b, w));
    if (graph.adjacent.contains(a)) {
      graph.adjacent[a] = std::map<std::string, W>();
    }
    graph.adjacent[a][b] = w;
  }
  return graph;
}

template <typename N, typename W>
std::ostream &operator<<(std::ostream &os, Arc<N, W> const &arc) {
  auto [a, b, w] = arc;
  os << "Arc<" << a << " -> " << b << " : " << w << ">";
  return os;
}
template <typename N, typename W>
std::ostream &operator<<(std::ostream &os, Graph<N, W> const &graph) {
  for (auto arc : graph)
    os << arc;
  return os;
}

} // namespace graph
