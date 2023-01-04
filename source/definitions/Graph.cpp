#include "../headers/Graph.h"

Graph::Graph(int n) : n(n), nodes(n) {}

void Graph::addEdge(int src, int dest, const string &airline) {
    auto it = find_if(nodes[src].edges.begin(), nodes[src].edges.end(), [dest](const Edge &e) { return e.dest == dest; });
    if (it == nodes[src].edges.end()) {
        nodes[src].edges.push_back({dest, {airline}});
    } else {
        it->airlines.insert(airline);
    }
}

void Graph::bfs(int src) {
    for (auto &node : nodes) {
        node.dist = -1;
        node.visited = false;
        node.previous.clear();
    }

    queue<int> q;
    q.push(src);
    nodes[src].dist = 0;
    nodes[src].visited = true;

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        for (auto &edge : nodes[node].edges) {
            if (!nodes[edge.dest].visited) {
                nodes[edge.dest].dist = nodes[node].dist + 1;
                nodes[edge.dest].visited = true;
                nodes[edge.dest].previous.push_back(node);
                q.push(edge.dest);
            } else if (nodes[edge.dest].dist == nodes[node].dist + 1) {
                nodes[edge.dest].previous.push_back(node);
            }
        }
    }
}

void Graph::bfs(set<int> src) {
    for (auto &node : nodes) {
        node.dist = -1;
        node.visited = false;
        node.previous.clear();
    }

    queue<int> q;
    for (auto &s : src) {
        q.push(s);
        nodes[s].dist = 0;
        nodes[s].visited = true;
    }

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        for (auto &edge : nodes[node].edges) {
            if (!nodes[edge.dest].visited) {
                nodes[edge.dest].dist = nodes[node].dist + 1;
                nodes[edge.dest].visited = true;
                nodes[edge.dest].previous.push_back(node);
                q.push(edge.dest);
            } else if (nodes[edge.dest].dist == nodes[node].dist + 1) {
                nodes[edge.dest].previous.push_back(node);
            }
        }
    }
}

vector<list<int>> Graph::shortestPaths(int src, int dest) {
    bfs(src);

    vector<list<int>> paths;
    if (nodes[dest].dist == -1) return paths;

    queue<list<int>> q;
    q.push({dest});

    while (!q.empty()) {
        list<int> path = q.front();
        q.pop();

        int node = path.front();
        if (node == src) {
            paths.push_back(path);
        } else {
            for (auto &previous : nodes[node].previous) {
                list<int> newPath = path;
                newPath.push_front(previous);
                q.push(newPath);
            }
        }
    }

    auto it = paths.begin();
    while (it != paths.end()) {
        if (it->size() != nodes[dest].dist + 1) {
            it = paths.erase(it);
        } else {
            it++;
        }
    }

    return paths;
}

vector<list<int>> Graph::shortestPaths(int src, int dest, const set<string> &airlines) {
    bfs(src);

    vector<list<int>> paths;
    if (nodes[dest].dist == -1) return paths;

    queue<list<int>> q;
    q.push({dest});

    while (!q.empty()) {
        list<int> path = q.front();
        q.pop();

        int node = path.front();
        if (node == src) {
            paths.push_back(path);
        } else {
            for (auto &previous : nodes[node].previous) {
                bool valid = false;
                for (auto &edge : nodes[previous].edges) {
                    if (edge.dest == node) {
                        for (auto &airline : edge.airlines) {
                            if (find(airlines.begin(), airlines.end(), airline) != airlines.end()) {
                                valid = true;
                                break;
                            }
                        }
                        break;
                    }
                }

                if (valid) {
                    list<int> newPath = path;
                    newPath.push_front(previous);
                    q.push(newPath);
                }
            }
        }
    }

    auto it = paths.begin();
    while (it != paths.end()) {
        if (it->size() != nodes[dest].dist + 1) {
            it = paths.erase(it);
        } else {
            it++;
        }
    }

    return paths;
}

vector<list<int>> Graph::shortestPaths(set<int> src, set<int> dest) {
    bfs(src);

    vector<list<int>> paths;
    for (auto &d : dest) {
        if (nodes[d].dist == -1) continue;

        queue<list<int>> q;
        q.push({d});

        while (!q.empty()) {
            list<int> path = q.front();
            q.pop();

            int node = path.front();
            if (find(src.begin(), src.end(), node) != src.end()) {
                paths.push_back(path);
            } else {
                for (auto &previous : nodes[node].previous) {
                    list<int> newPath = path;
                    newPath.push_front(previous);
                    q.push(newPath);
                }
            }
        }
        auto it = paths.begin();
        while (it != paths.end()) {
            if (it->size() != nodes[d].dist + 1) {
                it = paths.erase(it);
            } else {
                it++;
            }
        }
    }

    return paths;
}

vector<list<int>> Graph::shortestPaths(set<int> src, set<int> dest, const set<string> &airlines) {
    bfs(src);

    vector<list<int>> paths;
    for (auto &d : dest) {
        if (nodes[d].dist == -1) continue;

        queue<list<int>> q;
        q.push({d});

        while (!q.empty()) {
            list<int> path = q.front();
            q.pop();

            int node = path.front();
            if (find(src.begin(), src.end(), node) != src.end()) {
                paths.push_back(path);
            } else {
                for (auto &previous : nodes[node].previous) {
                    bool valid = false;
                    for (auto &edge : nodes[previous].edges) {
                        if (edge.dest == node) {
                            for (auto &airline : edge.airlines) {
                                if (find(airlines.begin(), airlines.end(), airline) != airlines.end()) {
                                    valid = true;
                                    break;
                                }
                            }
                            break;
                        }
                    }

                    if (valid) {
                        list<int> newPath = path;
                        newPath.push_front(previous);
                        q.push(newPath);
                    }
                }
            }
        }

        auto it = paths.begin();
        while (it != paths.end()) {
            if (it->size() != nodes[d].dist + 1) {
                it = paths.erase(it);
            } else {
                it++;
            }
        }
    }

    return paths;
}