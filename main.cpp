#include <bits/stdc++.h>

#include "source/headers/Graph.h"
#include "source/headers/Airport.h"
#include "source/headers/Airline.h"
#include "source/headers/Flight.h"

using namespace std;

struct eqAirport {
    bool operator()(const string a, const string b) const {
        return a == b;
    }
};

struct hashAirport {
    size_t operator()(const string a) const {
        return hash<string>()(a);
    }
};

typedef unordered_map<string, int, hashAirport, eqAirport> AirportMap;

// functions are declared here
void clearScreen();
void readAirports(AirportMap &airports);
void buildGraph(const AirportMap airports, Graph &graph);
void shortestPathMenu(const AirportMap airports, Graph graph);
void shortestPath(const AirportMap airports, Graph graph);

int main() {
    AirportMap airports;
    readAirports(airports);

    Graph graph(airports.size());
    buildGraph(airports, graph);

    clearScreen();
    cout << "  Welcome!" << endl;

    int option = -1;
    while (option != 0) {
        cout << " __________________________________________________ " << endl;
        cout << "  1 - Find the minimum route                        " << endl;
        cout << "  2 -                                               " << endl;
        cout << "  3 -                                               " << endl;
        cout << "                                                    " << endl;
        cout << "                                                    " << endl;
        cout << "  0 - Exit                                          " << endl;
        cout << " __________________________________________________ " << endl;
        cout << "  Option:";

        cin >> option;
        switch (option) {
            case 1:
                shortestPathMenu(airports, graph);
                break;
            case 2:
                cout << "  2" << endl;
                break;
            case 3:
                cout << "  3" << endl;
                break;
            case 0:
                break;
            default:
                cout << "  Invalid option" << endl;
                break;
        }
    }
}

void clearScreen() {
    cout << string(50, '\n');
}

void readAirports(AirportMap &airports) {
    ifstream file("../data/airports.csv");

    string line;
    getline(file, line); // skip first line

    while (getline(file, line)) {
        istringstream iss(line);
        string code;

        getline(iss, code, ',');
        airports.insert({code, airports.size() + 1});
    }
}

void buildGraph (const AirportMap airports, Graph &graph) {
    ifstream file("../data/flights.csv");

    string line;
    getline(file, line); // skip first line

    while (getline(file, line)) {
        istringstream iss(line);
        string airline, src, dest;

        getline(iss, src, ',');
        getline(iss, dest, ',');
        getline(iss, airline, ',');

        graph.addEdge(airports.at(src), airports.at(dest), airline);
    }
}

void shortestPathMenu(const AirportMap airports, Graph graph) {
    clearScreen();

    int option = -1;
    while (option != 0) {
        cout << "  Find the minimum route between:" << endl;
        cout << " __________________________________________________ " << endl;
        cout << "  1 - 2 airports                                    " << endl;
        cout << "  2 - 2 cities                                      " << endl;
        cout << "  3 - 2 locations                                   " << endl;
        cout << "                                                    " << endl;
        cout << "                                                    " << endl;
        cout << "  0 - Back                                          " << endl;
        cout << " __________________________________________________ " << endl;
        cout << "  Option:";
        cin >> option;

        switch (option) {
            case 1:
                shortestPath(airports, graph);
                break;
            case 2:
                cout << "  2" << endl;
                break;
            case 3:
                cout << "  3" << endl;
                break;
            case 0:
                break;
            default:
                cout << "  Invalid option" << endl;
                break;
        }
    }

    clearScreen();
}

void shortestPath(const AirportMap airports, Graph graph) {
    clearScreen();

    string src, dest;
    cout << "  Source airport code:";
    cin >> src;
    cout << "  Destination airport code:";
    cin >> dest;

    graph.printShortestPath(airports.at(src), airports.at(dest));
}