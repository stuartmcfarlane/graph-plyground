#include <map>
#include <string>
#include <sstream>
#include <utility>
#include <vector>
#include <algorithm>
#include <iostream>


using namespace std;

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
            if (!u[j] && (v == -1 || d[j] < d[v]))
            v = j;
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

pair<vector<string>, int> dijkstra_test(string start, string end, vector<string> arcs) {
    map<string, int> nodeIdx;
    vector<string> nodes;
    map<string, int> weights;
    vector<vector<pair<int, int>>> adj;
    int i = 0;
    
    for (auto lineIterator = arcs.begin(); lineIterator != arcs.end();
    lineIterator++) {
        string a, b;
        int w;
        stringstream ss(*lineIterator);
        ss >> a;
        ss >> b;
        ss >> w;
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
    
    i = 0;
    for (auto pA = adj.begin(); pA != adj.end(); *pA++, i++) {
        cout << nodes[i] << " : [";
        for (auto pB = pA->begin(); pB != pA->end(); *pB++) {
            auto b = *pB;
            cout << "(" << nodes[pB->first] << " " << " " << pB->second << ")";
        }
        cout << "]" << endl;
    }
    vector<int> d;
    vector<int> p;
    dijkstra(adj, nodeIdx[start], d, p);
    vector<int> path = restore_path(nodeIdx[start], nodeIdx[end], p);
    
    vector<string> nodePath;
    int distance = 0;
    string last;
    for (auto pIt = path.begin(); pIt != path.end(); *pIt++) {
        string node = nodes[*pIt];
        if (!last.empty()) {
            distance += weights[edgeKey(last, node)];
        }
        last = node;
        nodePath.push_back(node);
    }
    return pair<vector<string>, int>(nodePath, distance);
}
