#include "graph.h"
#include <map>
#include <string>
#include <utility>
#include <vector>
#include <algorithm>
#include <iostream>


using namespace std;
using namespace graph;

const int INF = 1000000000;

void dijkstra(vector<vector<pair<int, int>>> adj, int s, vector<int> &d, vector<int> &p) {
    
    int n = adj.size();
    d.assign(n, INF);
    p.assign(n, -1);
    vector<bool> u(n, false);
    
    d[s] = 0;
    for (int i = 0; i < n; i++) {
        int v = -1;
        for (int j = 0; j < n; j++) {
            if (!u[j] && (v == -1 || d[j] < d[v])) {
                v = j;
            }
        }
        
        if (d[v] == INF) break;
        
        u[v] = true;
        for (auto edge : adj[v]) {
            int to = edge.first;
            int len = edge.second;
            
            if (d[v] + len < d[to]) {
                d[to] = d[v] + len;
                p[to] = v;
            }
        }
    }
}
vector<int> restore_path(int s, int t, vector<int> const &p) {
    vector<int> path;
    
    for (int v = t; v != s; v = p[v]) {
        path.push_back(v);
    }
    path.push_back(s);
    
    reverse(path.begin(), path.end());
    return path;
}
string edgeKey(const string &a, const string &b) {
    if (a > b) {
        return edgeKey(b, a);
    }
    return a + ":" + b;
}

void print_adjacency(vector<string> nodes, vector<vector<pair<int, int>>> graph) {
    int i = 0;
    for (auto a : graph) {
        cout << nodes[i] << " : [";
        for (auto b : a) {
            cout << "(" << nodes[b.first] << " " << " " << b.second << ")";
        }
        cout << "]" << endl;
        i++;
    }
}

pair<vector<string>, int> dijkstra_path(string start, string end, Graph<string, float>graph) {
    map<string, int> nodeIdx;
    vector<string> nodes;
    map<string, int> weights;
    vector<vector<pair<int, int>>> adj;
    int i = 0;

    for (auto arc : graph.arcs) {
        auto [a, b, w] = arc;
        weights[edgeKey(a, b)] = w;
        if (nodeIdx.find(a) == nodeIdx.end()) {
            nodeIdx[a] = i++;
            nodes.push_back(a);
            adj.push_back(vector<pair<int, int>>());
        }
        if (nodeIdx.find(b) == nodeIdx.end()) {
            nodeIdx[b] = i++;
            nodes.push_back(b);
            adj.push_back(vector<pair<int, int>>());
        }
        adj[nodeIdx[a]].push_back(pair<int, int>(nodeIdx[b], w));
    }
    
    print_adjacency(nodes, adj);
    
    vector<int> d;
    vector<int> p;
    dijkstra(adj, nodeIdx[start], d, p);
    vector<int> path = restore_path(nodeIdx[start], nodeIdx[end], p);
    
    vector<string> nodePath;
    int distance = 0;
    string last;
    for (auto n : path) {
        string node = nodes[n];
        if (!last.empty()) {
            distance += weights[edgeKey(last, node)];
        }
        last = node;
        nodePath.push_back(node);
    }
    return pair<vector<string>, int>(nodePath, distance);
}
