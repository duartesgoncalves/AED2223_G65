#ifndef AIRLINE_H
#define AIRLINE_H

#include <bits/stdc++.h>

using namespace std;

class Airline {
    private:
        string code;
        string name;
        string callsign;
        string country;

    public:
        Airline(string code, string name, string callsign, string country);
        string getCode() const;
        string getName() const;
        string getCallsign() const;
        string getCountry() const;
};

#endif