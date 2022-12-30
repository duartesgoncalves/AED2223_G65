#ifndef GRAPH_H
#define GRAPH_H

#include <bits/stdc++.h>

using namespace std;

class Graph {
    struct Edge {
        int dest;
        list<string> airlines;
    };

    struct Node {
        list<Edge> edges;
        int dist = 0;
    };

    int n;
    vector<Node> nodes;

    public:
        explicit Graph(int n);
        void addEdge(int src, int dest, const string &airline);
        void bfs(int src, int dest);
        vector<int> shortestPath(int src, int dest);
        vector<int> shortestPath(int src, int dest, vector<string> &airlines);
};

#endif
