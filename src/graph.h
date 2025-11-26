#pragma once

#include <cmath>
#include <iostream>
#include <map>
#include <ostream>
#include <set>
#include <sstream>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

namespace graph {

template <typename NodeKeyType, typename WeightType = float>
using Arc = std::tuple<NodeKeyType, NodeKeyType, WeightType>;

template <typename NodeKeyType, typename WeightType = float>
using Adjacent = std::map<NodeKeyType, std::map<NodeKeyType, WeightType>>;

template <typename NodeKeyType, typename WeightType> struct Graph {
  std::set<NodeKeyType> nodes;
  std::vector<Arc<NodeKeyType, WeightType>> arcs;
  std::map<NodeKeyType, std::map<NodeKeyType, WeightType>> adjacent;

  template <typename NN> void addNode(const NN &node) {
    if (!this->nodes.contains(node)) {
      this->nodes.insert(node);
    }
  }

  void addArc(const Arc<NodeKeyType, WeightType> &arc) {
    auto [from, to, weight] = arc;
    this->addNode(from);
    this->addNode(to);
    this->arcs.push_back(arc);
    if (this->adjacent.contains(from)) {
      this->adjacent[from] = std::map<std::string, WeightType>();
    }
    this->adjacent[from][to] = weight;
  }
  WeightType weightOf(const NodeKeyType &from, const NodeKeyType &to, WeightType noArcWeight = INFINITY) const {
    if (!this->adjacent.contains(from)) {
      return noArcWeight;
    }
    if (!this->adjacent.at(from).contains(to)) { return noArcWeight; }
    return this->adjacent.at(from).at(to);
  }
};

template <typename WeightType>
Graph<std::string, WeightType>
lines2graph(std::vector<std::string> const &lines) {
  Graph<std::string, WeightType> graph;
  for (auto line : lines) {
    std::string a, b;
    WeightType w;
    std::stringstream ss(line);
    ss >> a;
    ss >> b;
    ss >> w;
    graph.addArc(Arc<std::string, WeightType>(a, b, w));
  }
  return graph;
}

template <typename NodeKeyType, typename WeightType>
std::ostream &operator<<(std::ostream &os, Arc<NodeKeyType, WeightType> const &arc) {
  auto [a, b, w] = arc;
  os << "Arc<" << a << " -> " << b << " : " << w << ">";
  return os;
}
template <typename NodeKeyType, typename WeightType>
std::ostream &operator<<(std::ostream &os, Graph<NodeKeyType, WeightType>
const &graph) {
  os << "Graph<" << graph.nodes.size() << ">" << std::endl;
  for (auto arc : graph.arcs)
    os << "  " << arc << std::endl;
  return os;
}

} // namespace graph
