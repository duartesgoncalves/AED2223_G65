#include "../headers/MenuHandler.h"

typedef unordered_map<string, int> CodeMap;
typedef unordered_map<int, Airport> AirportMap;
typedef unordered_map<string, set<int>> CityMap;

//TODO
void MenuHandler::clearScreen() {
    cout << string(50, '\n');
}

void MenuHandler::readAirports(CodeMap &codes, AirportMap &airports, CityMap &cities) {
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

        codes.insert({code, codes.size()});
        airports.insert({codes[code], Airport(code, name, city, country, latitude, longitude)});
        cities[city].insert(codes.size() - 1);
    }
}

void MenuHandler::buildGraph (const CodeMap codes, Graph &graph) {
    ifstream file("../data/flights.csv");

    string line;
    getline(file, line); // skip first line

    while (getline(file, line)) {
        istringstream iss(line);
        string airline, src, dest;

        getline(iss, src, ',');
        getline(iss, dest, ',');
        getline(iss, airline, ',');

        graph.addEdge(codes.at(src), codes.at(dest), airline);
    }
}

void MenuHandler::pathMenu(const CodeMap codes, const AirportMap airports, const CityMap cities, Graph graph) {
    clearScreen();

    int option = -1;
    while (option != 0) {
        cout << "  Find the minimum route between:" << endl;
        cout << " __________________________________________________ " << endl;
        cout << "  1 - codes                                         " << endl;
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
                pathAirports(codes, airports, graph, airlines);
                break;
            case 2:
                pathCities(codes, airports, cities, graph, airlines);
                break;
            case 3:
                pathLocations(codes, airports, graph, airlines);
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

set<string> MenuHandler::airlinePreference() {
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

void MenuHandler::pathAirports(const CodeMap codes, const AirportMap airports, Graph graph, set<string> airlines) {
    clearScreen();

    string src, dest;
    cout << "  Source airport code:";
    cin >> src;
    cout << "  Destination airport code:";
    cin >> dest;

    vector<list<int>> paths;
    if (airlines.empty()) {
        paths = graph.shortestPaths(codes.at(src), codes.at(dest));
    } else {
        paths = graph.shortestPaths(codes.at(src), codes.at(dest), airlines);
    }


    if (paths.size() == 0) cout << "  No route found" << endl;
    else {
        cout << "  Routes found:" << endl;
        for (auto &list : paths) {
            for (auto &airport : list) {
                cout << "    " << airports.at(airport).getName();
            }
            cout << endl;
        }
    }

    cout << endl << "  Press enter to continue...";
    cin.ignore(); cin.get();

    clearScreen();
}

void MenuHandler::pathCities(const CodeMap codes, const AirportMap airports, const CityMap cities, Graph graph, set<string> airlines) {
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
                cout << "    " << airports.at(airport).getName();
            }
            cout << endl;
        }
    }

    cout << endl << "  Press enter to continue...";
    cin.ignore(); cin.get();

    clearScreen();
}

void MenuHandler::pathLocations(const CodeMap codes, AirportMap airports, Graph graph, set<string> airlines) {
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

    for (auto &pair : airports) {
        if (pair.second.distance(srcLat, srcLong) <= range) srcAirports.insert(pair.first);
        if (pair.second.distance(destLat, destLong) <= range) destAirports.insert(pair.first);
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
                cout << "    " << airports.at(airport).getName();
            }
            cout << endl;
        }
    }

    cout << endl << "  Press enter to continue...";
    cin.ignore(); cin.get();

    clearScreen();
}

void MenuHandler::airportStats(const CodeMap codes, const AirportMap airports, Graph graph) {
    clearScreen();

    cout << "  Airport code:";
    string code;
    cin >> code;

    clearScreen();

    if (codes.find(code) == codes.end()) {
        cout << "  Invalid airport code" << endl;
        cout << endl << "  Press enter to continue...";
        cin.ignore(); cin.get();
        clearScreen();
        return;
    }

    int airport = codes.at(code);
    set<int> destinations = graph.getDestinations(airport);

    cout << "  Number of flights departing from " << code << ": " << graph.getNumOutgoing(airport) << endl;
    cout << "  Number of airlines operating from " << code << ": " << graph.getNumAirlines(airport) << endl;
    cout << "  Number of destinations from " << code << ": " << destinations.size() << endl;

    set<string> cities, countries;
    for (auto &dest : destinations) {
        cities.insert(airports.at(dest).getCity());
        countries.insert(airports.at(dest).getCountry());
    }

    cout << "  Number of cities with direct flights from " << code << ": " << cities.size() << endl;
    cout << "  Number of countries with direct flights from " << code << ": " << countries.size() << endl;

    cout << endl << "  Set number of maximum flights:";
    int hops;
    cin >> hops;
    cout << endl;

    set<int> reachable = graph.reachable(airport, hops);

    cout << "  Number of airports reachable from " << code << " in " << hops << " flights: " << reachable.size() << endl;

    cities.clear();
    countries.clear();
    for (auto &dest : reachable) {
        cities.insert(airports.at(dest).getCity());
        countries.insert(airports.at(dest).getCountry());
    }

    cout << "  Number of cities reachable from " << code << " in " << hops << " flights: " << cities.size() << endl;
    cout << "  Number of countries reachable from " << code << " in " << hops << " flights: " << countries.size() << endl;

    cout << endl << "  Press enter to continue...";
    cin.ignore(); cin.get();

    clearScreen();
}