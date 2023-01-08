#ifndef AIRPORT_H
#define AIRPORT_H

#include <bits/stdc++.h>

using namespace std;
/**
 * @brief The Airport class
 * This class is used to store the information of the airport
 */
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
        double distance(double lat, double lon) const;
};

#endif
