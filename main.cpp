#include <bits/stdc++.h>

#include "source/headers/Graph.h"
#include "source/headers/Airport.h"


using namespace std;

typedef unordered_map<string, int> AirportMap;
typedef unordered_map<string, set<int>> CityMap;

struct airportEq {
    bool operator()(const Airport &a, const Airport &b) const {
        return a.getCode() == b.getCode();
    }
};

struct airportHash {
    size_t operator()(const Airport &a) const {
        return hash<string>()(a.getCode());
    }
};

typedef unordered_set<Airport, airportHash, airportEq> AirportSet;

// functions are declared here
void clearScreen();
void readAirports(AirportMap &airports, AirportSet &airportSet, CityMap &cities);
void buildGraph(const AirportMap airports, Graph &graph);
void pathMenu(const AirportMap airports, const AirportSet airportSet, const CityMap cities, Graph graph);
set<string> airlinePreference();
void pathAirports(const AirportMap airports, Graph graph, set<string> airlines);
void pathCities(const AirportMap airports, CityMap cities, Graph graph, set<string> airlines);
void pathLocations(const AirportMap airports, const AirportSet airportSet, Graph graph, set<string> airlines);

int main() {
    AirportMap airports; CityMap cities; AirportSet airportSet;
    readAirports(airports, airportSet, cities);

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
                pathMenu(airports, airportSet, cities, graph);
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

void readAirports(AirportMap &airports, AirportSet &airportSet, CityMap &cities) {
    ifstream file("../data/airports.csv");

    string line;
    getline(file, line); // skip first line

    while (getline(file, line)) {
        istringstream iss(line);
        string code; string name; string city; string country; double latitude; double longitude;

        getline(iss, code, ',');
        getline(iss, name, ',');
        getline(iss, city, ',');
        getline(iss, country, ',');
        iss >> latitude;
        iss.ignore();
        iss >> longitude;

        airports.insert({code, airports.size()});
        airportSet.insert(Airport(code, name, city, country, latitude, longitude));
        cities[city].insert(airports.size() - 1);
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

void pathMenu(const AirportMap airports, const AirportSet airportSet, const CityMap cities, Graph graph) {
    clearScreen();

    int option = -1;
    while (option != 0) {
        cout << "  Find the minimum route between:" << endl;
        cout << " __________________________________________________ " << endl;
        cout << "  1 - airports                                      " << endl;
        cout << "  2 - cities                                        " << endl;
        cout << "  3 - locations (coordinates)                       " << endl;
        cout << "                                                    " << endl;
        cout << "                                                    " << endl;
        cout << "  0 - Back                                          " << endl;
        cout << " __________________________________________________ " << endl;
        cout << "  Option:";
        cin >> option;

        set<string> airlines;
        if (option == 1 || option == 2 || option == 3) airlines = airlinePreference();

        switch (option) {
            case 1:
                pathAirports(airports, graph, airlines);
                break;
            case 2:
                pathCities(airports, cities, graph, airlines);
                break;
            case 3:
                pathLocations(airports, airportSet, graph, airlines);
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

set<string> airlinePreference() {
    clearScreen();

    int option = -1;
    cout << "  Do you have a preference for an airline? no (0) / yes (1): " << endl;
    while (option != 0 && option != 1) { cout << "  Option:"; cin >> option; cout << endl; }

    set<string> airlines;
    if (option == 1) {
        cout << "  Enter the airlines codes and press enter (0 to finish):" << endl;
        string airline;
        while (airline != "0") {
            cout << "  Airline:";
            cin >> airline;
            if (airline != "0") airlines.insert(airline);
        }
    }

    return airlines;
}

void pathAirports(const AirportMap airports, Graph graph, set<string> airlines) {
    clearScreen();

    string src, dest;
    cout << "  Source airport code:";
    cin >> src;
    cout << "  Destination airport code:";
    cin >> dest;

    vector<list<int>> paths;
    if (airlines.empty()) {
        paths = graph.shortestPaths(airports.at(src), airports.at(dest));
    } else {
        paths = graph.shortestPaths(airports.at(src), airports.at(dest), airlines);
    }


    if (paths.size() == 0) cout << "  No route found" << endl;
    else {
        cout << "  Routes found:" << endl;
        for (auto &list : paths) {
            for (auto &airport : list) {
                for (auto &pair : airports) {
                    if (pair.second == airport) {
                        cout << "    " << pair.first;
                        break;
                    }
                }
            }
            cout << endl;
        }
    }

    cout << endl << "  Press enter to continue...";
    cin.ignore(); cin.get();

    clearScreen();
}

void pathCities(const AirportMap airports, CityMap cities, Graph graph, set<string> airlines) {
    clearScreen();

    string src, dest;
    cout << "  Source city:";
    cin >> src;
    cout << "  Destination city:";
    cin >> dest;

    vector<list<int>> paths;
    if (airlines.empty()) {
        paths = graph.shortestPaths(cities.at(src), cities.at(dest));
    } else {
        paths = graph.shortestPaths(cities.at(src), cities.at(dest), airlines);
    }


    if (paths.size() == 0) cout << "  No route found" << endl;
    else {
        cout << "  Routes found:" << endl;
        for (auto &list : paths) {
            for (auto &airport : list) {
                for (auto &pair : airports) {
                    if (pair.second == airport) {
                        cout << "    " << pair.first;
                        break;
                    }
                }
            }
            cout << endl;
        }
    }

    cout << endl << "  Press enter to continue...";
    cin.ignore(); cin.get();

    clearScreen();
}

void pathLocations(const AirportMap airports, AirportSet airportSet, Graph graph, set<string> airlines) {
    clearScreen();

    double srcLat, srcLong, destLat, destLong, range;
    cout << "  Source latitude:";
    cin >> srcLat;
    cout << "  Source longitude:";
    cin >> srcLong;
    cout << endl << "  Destination latitude:";
    cin >> destLat;
    cout << "  Destination longitude:";
    cin >> destLong;

    cout << endl << "  Specify the range:";
    cin >> range;

    set<int> srcAirports, destAirports;

    for (auto &airport : airportSet) {
        if (airport.distance(srcLat, srcLong) <= range) srcAirports.insert(airports.at(airport.getCode()));
        if (airport.distance(destLat, destLong) <= range) destAirports.insert(airports.at(airport.getCode()));
    }

    if (srcAirports.empty() || destAirports.empty()) {
        cout << "  No airports found in the specified range" << endl;
        cout << endl << "  Press enter to continue...";
        cin.ignore(); cin.get();
        clearScreen();
        return;
    }

    vector<list<int>> paths;
    if (airlines.empty()) {
        paths = graph.shortestPaths(srcAirports, destAirports);
    } else {
        paths = graph.shortestPaths(srcAirports, destAirports, airlines);
    }

    if (paths.size() == 0) cout << "  No route found" << endl;
    else {
        cout << "  Routes found:" << endl;
        for (auto &list : paths) {
            for (auto &airport : list) {
                for (auto &pair : airports) {
                    if (pair.second == airport) {
                        cout << "    " << pair.first;
                        break;
                    }
                }
            }
            cout << endl;
        }
    }

    cout << endl << "  Press enter to continue...";
    cin.ignore(); cin.get();

    clearScreen();
}