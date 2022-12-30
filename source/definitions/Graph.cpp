#include "../headers/Graph.h"

Graph::Graph(int n) : n(n), nodes(n) {}

void Graph::addEdge(int src, int dest, const string &airline) {
    auto it = find_if(nodes[src].edges.begin(), nodes[src].edges.end(), [dest](const Edge &e) { return e.dest == dest; });
    if (it == nodes[src].edges.end()) {
        nodes[src].edges.push_back({dest, {airline}});
    } else {
        it->airlines.push_back(airline);
    }
}

void Graph::bfs(int src, int dest) {
    queue<int> q;
    q.push(src);
    nodes[src].dist = 0;

    vector<bool> visited(n, false);

    visited[src] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        if (u == dest) {
            break;
        }

        for (const auto &edge : nodes[u].edges) {
            if (!visited[edge.dest]) {
                visited[edge.dest] = true;
                nodes[edge.dest].dist = nodes[u].dist + 1;
                q.push(edge.dest);
            }
        }
    }
}

vector<int> Graph::shortestPath(int src, int dest) {
    bfs(src, dest);

    if (nodes[dest].dist == 0) {
        return {};
    }

    if (nodes[dest].dist == 1) {
        return {src, dest};
    }

    vector<int> path;
    path.push_back(dest);

    auto u = dest;
    while (u != src) {
        for (const auto &e : nodes[u].edges) {
            if (nodes[e.dest].dist == nodes[u].dist - 1) {
                path.push_back(e.dest);
                u = e.dest;
                break;
            }
        }
    }

    reverse(path.begin(), path.end());
    return path;
}

vector<int> Graph::shortestPath(int src, int dest, vector<string> &airlines) {
    bfs(src, dest);

    if (nodes[dest].dist == 0) {
        return {};
    }

    if (nodes[dest].dist == 1) {
        return {src, dest};
    }

    vector<int> path;
    path.push_back(dest);

    auto u = dest;
    while (u != src) {
        for (const auto &e : nodes[u].edges) {
            if (nodes[e.dest].dist == nodes[u].dist - 1) {
                auto it = find_if(e.airlines.begin(), e.airlines.end(), [&airlines](const string &airline) {
                    return find(airlines.begin(), airlines.end(), airline) != airlines.end();
                });

                if (it != e.airlines.end()) {
                    path.push_back(e.dest);
                    u = e.dest;
                    break;
                }
            }
        }
    }

    reverse(path.begin(), path.end());
    return path;
}