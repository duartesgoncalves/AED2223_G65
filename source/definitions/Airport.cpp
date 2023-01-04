#include <utility>

#include "../headers/Airport.h"

Airport::Airport(string code, string name, string city, string country, double latitude, double longitude) {
    this->code = std::move(code);
    this->name = std::move(name);
    this->city = std::move(city);
    this->country = std::move(country);
    this->latitude = latitude;
    this->longitude = longitude;
}

string Airport::getCode() const {
    return code;
}

string Airport::getName() const {
    return name;
}

string Airport::getCity() const {
    return city;
}

string Airport::getCountry() const {
    return country;
}

double Airport::getLatitude() const {
    return latitude;
}

double Airport::getLongitude() const {
    return longitude;
}

double Airport::distance(double lat, double lon) const {
    double x = (lon - longitude) * cos((latitude + lat) / 2);
    double y = lat - latitude;
    return sqrt(x * x + y * y) * 6371;
}