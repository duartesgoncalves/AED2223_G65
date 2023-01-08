#ifndef AED2223_GXX_MENUHANDLER_H
#define AED2223_GXX_MENUHANDLER_H

#include <bits/stdc++.h>

#include "Graph.h"
#include "Airport.h"

using namespace std;

typedef unordered_map<string, int> CodeMap;
typedef unordered_map<int, Airport> AirportMap;
typedef unordered_map<string, set<int>> CityMap;

/**
 * @brief The MenuHandler class
 * This class is used to handle the menu, the user input and the program flow.
 */
class MenuHandler {
    public:
    void clearScreen();
    void readAirports(CodeMap &codes, AirportMap &airports, CityMap &cities);
    void buildGraph(const CodeMap codes, Graph &graph);
    void pathMenu(const CodeMap codes, const AirportMap airports, const CityMap cities, Graph graph);
    set<string> airlinePreference();
    void pathAirports(const CodeMap codes, const AirportMap airports, Graph graph, set<string> airlines);
    void pathCities(const CodeMap codes, const AirportMap airports, const CityMap cities, Graph graph, set<string> airlines);
    void pathLocations(const CodeMap codes, const AirportMap airports, Graph graph, set<string> airlines);
    void airportStats(const CodeMap codes, const AirportMap airports, Graph graph);
};


#endif //AED2223_GXX_MENUHANDLER_H
