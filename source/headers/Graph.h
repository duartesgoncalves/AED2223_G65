#ifndef GRAPH_H
#define GRAPH_H

#include <bits/stdc++.h>

using namespace std;

/**
 * @brief The Graph class
 * This class represents the graph data structure
 */
class Graph {
    struct Edge {
        int dest;
        set<string> airlines;
    };

    struct Node {
        list<Edge> edges;
        int dist = -1;
        bool visited = false;
        vector<int> previous;
    };

    int n;
    vector<Node> nodes;

    public:
        explicit Graph(int n);
        void addEdge(int src, int dest, const string &airline);
        void bfs(int src);
        void bfs(set<int> src);
        vector<list<int>> shortestPaths(int src, int dest);
        vector<list<int>> shortestPaths(int src, int dest, const set<string> &airlines);
        vector<list<int>> shortestPaths(set<int> src, set<int> dest);
        vector<list<int>> shortestPaths(set<int> src, set<int> dest, const set<string> &airlines);
        int getNumOutgoing(int src) const;
        int getNumAirlines(int src) const;
        set<int> getDestinations(int src) const;
        set<int> reachable(int src, int hops);
};

#endif
