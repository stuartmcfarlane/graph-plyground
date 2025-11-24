#pragma once

#include <string>
#include <vector>
#include <tuple>
#include <utility>
#include <sstream>

namespace graph {
    
    template <typename W>
    using
    Arc = std::tuple<std::string, std::string, W>;
    
    template <typename W> struct ArcXY {
        Arc<W> arc;
        float x;
        float y;
    };
    
    template <typename W> using Graph = std::vector<Arc<W>>;

    template <typename W>
    using Adjacency = std::vector<std::vector<std::pair<int, W>>>;

    template <typename W>
    Graph<W> lines2graph(std::vector<std::string> const &lines) {
      Graph<W> graph;
      for (auto line : lines) {
        std::string a, b;
        int w;
        std::stringstream ss(line);
        ss >> a;
        ss >> b;
        ss >> w;
        graph.push_back(Arc<W>(a, b, w));
      }
      return graph;
    }

    template <typename W>
    std::ostream &operator<<(std::ostream &os, Arc<W> const& arc) {
        auto [a, b, w] = arc;
        os << "Arc<" << a << " -> " << b << " : " << w << ">";
        return os;
    }
    template <typename W>
    std::ostream &operator<<(std::ostream &os, ArcXY<W> const& arcXY) {
        os << "ArcXY<" << arcXY.arc << " (" << arcXY.x << ", " << arcXY.y
        << ")"
        << ">";
        return os;
    }
    template <typename W>
    std::ostream &operator<<(std::ostream &os, Graph<W> const& graph) {
        for (auto arc : graph) os << arc;
        return os;
    }
    
} // namespace graph
