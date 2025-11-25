// #include <string>
#include <vector>
#include <utility>
#include "graph.h"

std::pair<std::vector<std::string>, int> dijkstra_path(std::string start, std::string end, 
                                        graph::Graph<std::string, float> graph);
