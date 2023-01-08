#include <utility>

#include "../headers/Airport.h"

/**
 * @brief Airport::Airport
 * This is the Airport constructor. It receives the airport code, its name, city, country, latitude and longitude.
 * Complexity: O(1)
 * @param name - The name of the airport
 * @param code - The code of the airport
 * @param city - The city of the airport
 * @param country - The country of the airport
 * @param latitude - The latitude of the airport
 * @param longitude - The longitude of the airport
 */
Airport::Airport(string code, string name, string city, string country, double latitude, double longitude) {
    this->code = std::move(code);
    this->name = std::move(name);
    this->city = std::move(city);
    this->country = std::move(country);
    this->latitude = latitude;
    this->longitude = longitude;
}

/**
 * @brief Airport::getCode
 * This function returns the code of the airport.
 * Complexity: O(1)
 * @return The code of the airport.
 */
string Airport::getCode() const {
    return code;
}

/**
 * @brief Airport::getName
 * This function returns the name of the airport.
 * Complexity: O(1)
 * @return The name of the airport.
 */
string Airport::getName() const {
    return name;
}

/**
 * @brief Airport::getCity
 * This function returns the city of the airport.
 * Complexity: O(1)
 * @return The city of the airport.
 */
string Airport::getCity() const {
    return city;
}

/**
 * @brief Airport::getCountry
 * This function returns the country of the airport.
 * Complexity: O(1)
 * @return The country of the airport.
 */
string Airport::getCountry() const {
    return country;
}

/**
 * @brief Airport::getLatitude
 * This function returns the latitude of the airport.
 * Complexity: O(1)
 * @return The latitude of the airport.
 */
double Airport::getLatitude() const {
    return latitude;
}

/**
 * @brief Airport::getLongitude
 * This function returns the longitude of the airport.
 * Complexity: O(1)
 * @return The longitude of the airport.
 */
double Airport::getLongitude() const {
    return longitude;
}

/**
 * @brief Airport::getDistance
 * This function returns the distance between two airports (using their latitude and longitude).
 * Complexity: O(1)
 * @param airport - The airport to which the distance is calculated (destination).
 * @return The distance between the two airports.
 */
double Airport::distance(double lat, double lon) const {
    double x = (lon - longitude) * cos((latitude + lat) / 2);
    double y = lat - latitude;
    return sqrt(x * x + y * y) * 6371;
}