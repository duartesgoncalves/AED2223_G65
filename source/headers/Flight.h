#ifndef FLIGHT_H
#define FLIGHT_H

#include <bits/stdc++.h>

using namespace std;

/**
 * @brief The Flight class
 * This class is used to store the information of the flight
 */
class Flight {
    private:
        string source;
        string target;
        string airline;

    public:
        Flight(string source, string target, string airline);
        string getSource() const;
        string getTarget() const;
        string getAirline() const;
};

#endif