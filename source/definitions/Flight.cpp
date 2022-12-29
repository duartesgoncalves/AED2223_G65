#include <utility>

#include "../headers/Flight.h"

Flight::Flight(string source, string target, string airline) {
    this->source = std::move(source);
    this->target = std::move(target);
    this->airline = std::move(airline);
}

string Flight::getSource() const {
    return source;
}

string Flight::getTarget() const {
    return target;
}

string Flight::getAirline() const {
    return airline;
}