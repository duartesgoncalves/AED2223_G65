#include "../headers/Graph.h"

/**
 * @brief Graph::Graph
 * This is the Graph constructor. It receives the amount of nodes the graph will have. It initializes the nodes vector with the given amount of nodes.
 * Complexity: O(1)
 * @param n - The amount of nodes the graph will have.
 */
Graph::Graph(int n) : n(n), nodes(n) {}

/**
 * @brief Graph::addEdge
 * This function adds an edge to the graph. It receives the source node, the destination node and the airline that flies between the two nodes.
 * Complexity: O(N)
 * @param src - The source node.
 * @param dest - The destination node.
 * @param airline - The airline that flies between the two nodes.
 */
void Graph::addEdge(int src, int dest, const string &airline) {
    auto it = find_if(nodes[src].edges.begin(), nodes[src].edges.end(), [dest](const Edge &e) { return e.dest == dest; });
    if (it == nodes[src].edges.end()) {
        nodes[src].edges.push_back({dest, {airline}});
    } else {
        it->airlines.insert(airline);
    }
}

/**
 * @brief Graph::bfs
 * This function performs a breadth-first search on the graph, starting at the given node. It sets the distance of each node to the given node, and the previous nodes of each node.
 * Complexity: O(V + E)
 * @param src - The node to start the search at.
 */
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

/**
 * @brief Graph::bfs
 * This function performs a breadth-first search on the graph, starting at the given nodes. It sets the distance of each node to the given nodes, and the previous nodes of each node.
 * Complexity: O(V + E)
 * @param src - A set of nodes to start the search at.
 */
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

/**
 * @brief Graph::shortestPaths
 * This function returns all the shortest paths between the given nodes.
 * Complexity: O(V + E)
 * @param src - The source node.
 * @param dest - The destination node.
 * @return A vector of lists of integers, where each list represents a path.
 */
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

/**
 * @brief Graph::shortestPaths
 * This function returns all the shortest paths between the given nodes.
 * Complexity: O(V + E)
 * @param src - A set of source nodes.
 * @param dest - A set of destination nodes.
 * @param airlines - A set of desired airlines.
 * @return A vector of lists of integers, where each list represents a path.
 */
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

/**
 * @brief Graph::shortestPaths
 * This function returns all the shortest paths between the given nodes.
 * Complexity: O(V(V + E))
 * @param src - A set of source nodes.
 * @param dest - A set of destination nodes.
 * @param airlines - A set of desired airlines.
 * @return A vector of lists of integers, where each list represents a path.
 */
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

/**
 * @brief Graph::shortestPaths
 * This function returns all the shortest paths between the given nodes.
 * Complexity: O(V(V + E))
 * @param src - A set of source nodes.
 * @param dest - A set of destination nodes.
 * @param airlines - A set of desired airlines.
 * @return A vector of lists of integers, where each list represents a path.
 */
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

/**
 * @brief Graph::getNumOutgoing
 * This function returns the number of flights that depart from the desired airport.
 * Complexity: O(1)
 * @param src - The source node (airport).
 * @return The number of flights that depart from the desired airport.
 */
int Graph::getNumOutgoing(int src) const {
    return nodes[src].edges.size();
}

/**
 * @brief Graph::getNumAirlines
 * This function returns the number of airlines that operate on desired airport.
 * Complexity: O(E)
 * @param src - The source node (airport).
 * @return The number of airlines that operate on desired airport.
 */
int Graph::getNumAirlines(int src) const {
    set<string> airlines;
    for (auto &edge : nodes[src].edges) {
        for (auto &airline : edge.airlines) {
            airlines.insert(airline);
        }
    }
    return airlines.size();
}

/**
 * @brief Graph::getDestinations
 * This function returns a set of all the destinations that can be reached from the desired airport.
 * Complexity: O(E)
 * @param src - The source node (airport).
 * @return A set of all the destinations that can be reached from the desired airport.
 */
set<int> Graph::getDestinations(int src) const {
    set<int> destinations;
    for (auto &edge : nodes[src].edges) {
        destinations.insert(edge.dest);
    }
    return destinations;
}

/**
 * @brief Graph::reachable
 * This function returns a set of all the airlines that operate on the desired airport.
 * Complexity: O(V + E)
 * @param src - The source node (airport).
 * @param hops - The maximum number of hops.
 * @return A set of all the airports that are reachable within a maximum of n hops (represented by the hops parameter).
 */
set<int> Graph::reachable(int src, int hops) {
    set<int> reachable;

    bfs(src);

    for (int i = 0; i < nodes.size(); i++) {
        if (nodes[i].dist <= hops && nodes[i].dist != -1) {
            reachable.insert(i);
        }
    }

    return reachable;
}