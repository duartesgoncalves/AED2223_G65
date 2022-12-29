#include <utility>

#include "../headers/Airline.h"

Airline::Airline(string code, string name, string callsign, string country) {
    this->code = std::move(code);
    this->name = std::move(name);
    this->callsign = std::move(callsign);
    this->country = std::move(country);
}

string Airline::getCode() const {
    return code;
}

string Airline::getName() const {
    return name;
}

string Airline::getCallsign() const {
    return callsign;
}

string Airline::getCountry() const {
    return country;
}