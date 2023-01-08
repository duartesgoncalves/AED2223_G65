#include <bits/stdc++.h>

#include "source/headers/Graph.h"
#include "source/headers/Airport.h"
#include "source/headers/MenuHandler.h"

using namespace std;

int main() {
    auto handler = new MenuHandler();
    CodeMap codes; AirportMap airports; CityMap cities;
    handler->readAirports(codes, airports, cities);

    Graph graph(codes.size());
    handler->buildGraph(codes, graph);

    handler->clearScreen();
    cout << "  Welcome!" << endl;

    int option = -1;
    while (option != 0) {
        cout << " __________________________________________________ " << endl;
        cout << "  1 - Find the minimum route                        " << endl;
        cout << "  2 - Airport stats                                 " << endl;
        cout << "  3 -                                               " << endl;
        cout << "                                                    " << endl;
        cout << "                                                    " << endl;
        cout << "  0 - Exit                                          " << endl;
        cout << " __________________________________________________ " << endl;
        cout << "  Option:";

        cin >> option;
        switch (option) {
            case 1:
                handler->pathMenu(codes, airports, cities, graph);
                break;
            case 2:
                handler->airportStats(codes, airports, graph);
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