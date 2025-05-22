#include "WhoWasWere.hpp"


using std::unordered_map;
using std::pair;
using std::vector;
using std::string;
using std::set;

WhoWasWere::WhoWasWere(unordered_map<int, vector<pair<std::time_t, pair<double, double>>>>& logs_,
					   unordered_map<string, pair<pair<double, double>, pair<double, double>>>& places_) : logs(logs_), places(places_) {
    fillGridIndex();

}

unordered_map<int, set<pair<std::time_t, string>>> WhoWasWere::getUserData() {

    for (auto& [user_id, locals] : logs) {
        for (auto& [timestamp, coords] : locals) {
            std::pair<int, int> cell = getGridCell(coords.first, coords.second);
            for (auto& local : gridIndex[cell]) {
                userData[user_id].insert({timestamp, local});
            }
        }
    }
    return userData;
}

void WhoWasWere::fillGridIndex() {
    for (auto& [place, coords] : places) {
        for (double x = coords.first.first; x <= coords.second.first; x += scale) {
            for (double y = coords.first.second; y <= coords.second.second; y += scale) {

                std::pair<int, int> cell = getGridCell(x, y);
                gridIndex[cell].insert(place);
            }
        }
    }
}

std::pair<int, int> WhoWasWere::getGridCell(double lat, double lon) const {
    int latKey = static_cast<int>(lat / scale);
    int lonKey = static_cast<int>(lon / scale);
    return { latKey, lonKey };
}