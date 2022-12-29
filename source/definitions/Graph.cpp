#include "../headers/Graph.h"

Graph::Graph(int n) : n(n), nodes(n+1) {}

void Graph::addEdge(int src, int dest, const string &airline) {
    auto it = find_if(nodes[src].edges.begin(), nodes[src].edges.end(), [dest](const Edge &e) { return e.dest == dest; });
    if (it == nodes[src].edges.end()) {
        nodes[src].edges.push_back({src, dest, {airline}});
    } else {
        it->airlines.push_back(airline);
    }
}

void Graph::bfs(int src) {
    queue<int> q;
    q.push(src);
    nodes[src].dist = 0;

    vector<bool> visited(n+1, false);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        if (visited[u]) continue;
        visited[u] = true;

        for (const auto &edge : nodes[u].edges) {
            if (!visited[edge.dest]) {
                nodes[edge.dest].dist = nodes[u].dist + 1;
                q.push(edge.dest);
            }
        }
    }
}

void Graph::printShortestPath(int src, int dest) {
    bfs(src);

    if (nodes[dest].dist == 0) {
        cout << "  No path found" << endl;
        return;
    }

    cout << "  " << nodes[dest].dist << " hops" << endl;
    cout << "  " << src << " -> ";

    int u = src;
    while (u != dest) {
        for (const auto &edge : nodes[u].edges) {
            if (nodes[edge.dest].dist == nodes[u].dist - 1) {
                cout << edge.dest << " -> ";
                u = edge.dest;
                break;
            }
        }
    }

    cout << dest << endl;
}