#pragma once
#include <string>
#include <ctime>

struct Coordinates {
    double lat;
    double lon;
};

struct BoundingBox {
    Coordinates topLeft;
    Coordinates bottomRight;
};

struct UserLogEntry {
    std::time_t timestamp;
    Coordinates coords;
};

struct UserVisit {
    std::time_t timestamp;
    std::string place;

    bool operator<(const UserVisit& other) const {
        return timestamp < other.timestamp ||
            (timestamp == other.timestamp && place < other.place);
    }
};