#pragma once

#include <string>
#include <vector>
#include <tuple>
#include <utility>
#include <sstream>
#include <iostream>

namespace graph {
    
    template <typename W>
    using
    Arc = std::tuple<std::string, std::string, W>;
    
    template <typename W> using Graph = std::vector<Arc<W>>;
    template <typename W>
    using Adjacency = std::vector<std::vector<std::pair<int, W>>>;
    
    template <typename W> void print_graph(Graph<W> graph) {
        for (auto arc : graph) {
            auto [a, b, w] = arc;
            std::cout << a << ">--" << w << "-->" << b << std::endl;
        }
    }
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
}
