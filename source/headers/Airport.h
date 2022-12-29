#ifndef AIRPORT_H
#define AIRPORT_H

#include <bits/stdc++.h>

using namespace std;

class Airport {
    private:
        string code;
        string name;
        string city;
        string country;
        double latitude;
        double longitude;

    public:
        Airport(string code, string name, string city, string country, double latitude, double longitude);
        string getCode() const;
        string getName() const;
        string getCity() const;
        string getCountry() const;
        double getLatitude() const;
        double getLongitude() const;
};

#endif
