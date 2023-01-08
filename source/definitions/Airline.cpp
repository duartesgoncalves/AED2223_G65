#include <utility>

#include "../headers/Airline.h"

/**
 * @brief Airline::Airline
 * This is the Airline constructor. It receives the airline code, its name, callsign and the country it belongs to.
 * Complexity: O(1)
 * @param code - The code of the class.
 * @param name - The course of the class.
 * @param callsign - The callsign of the airline.
 * @param country - The country of the airline.
 */
Airline::Airline(string code, string name, string callsign, string country) {
    this->code = std::move(code);
    this->name = std::move(name);
    this->callsign = std::move(callsign);
    this->country = std::move(country);
}

/**
 * @brief Airline::getCode
 * This function returns the code of the airline.
 * Complexity: O(1)
 * @return The code of the airline.
 */
string Airline::getCode() const {
    return code;
}

/**
 * @brief Airline::getName
 * This function returns the name of the airline.
 * Complexity: O(1)
 * @return The name of the airline.
 */
string Airline::getName() const {
    return name;
}

/**
 * @brief Airline::getCallsign
 * This function returns the callsign of the airline.
 * Complexity: O(1)
 * @return The callsign of the airline.
 */
string Airline::getCallsign() const {
    return callsign;
}

/**
 * @brief Airline::getCountry
 * This function returns the country of the airline.
 * Complexity: O(1)
 * @return The country of the airline.
 */
string Airline::getCountry() const {
    return country;
}