#include <utility>

#include "../headers/Flight.h"

/**
 * @brief Flight::Flight
 * This is the Flight constructor. It receives the departure airport (source), arrival airport (target) and the airline.
 * Complexity: O(1)
 * @param source - The departure airport
 * @param target - The arrival airport
 * @param airline - The airline of the flight
 */
Flight::Flight(string source, string target, string airline) {
    this->source = std::move(source);
    this->target = std::move(target);
    this->airline = std::move(airline);
}

/**
 * @brief Flight::getSource
 * This function returns the departure airport of the flight.
 * Complexity: O(1)
 * @return The departure airport of the flight.
 */
string Flight::getSource() const {
    return source;
}

/**
 * @brief Flight::getTarget
 * This function returns the arrival airport of the flight.
 * Complexity: O(1)
 * @return The arrival airport of the flight.
 */
string Flight::getTarget() const {
    return target;
}

/**
 * @brief Flight::getAirline
 * This function returns the airline of the flight.
 * Complexity: O(1)
 * @return The airline of the flight.
 */
string Flight::getAirline() const {
    return airline;
}