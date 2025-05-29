#include "WhoWasWere.hpp"
#include "DataTypes.hpp"


using std::unordered_map;
using std::pair;
using std::vector;
using std::string;
using std::set;

WhoWasWere::WhoWasWere(unordered_map<int, vector<UserLogEntry>>& logs_, unordered_map<string, BoundingBox>& places_)
    : logs(logs_), places(places_) {}


unordered_map<int, set<UserVisit>> WhoWasWere::getUserData() {
    for (const auto& [user_id, userLogs] : logs) {
        for (const auto& userLog : userLogs) {

            for (const auto& [placeName, box] : places) {

                auto lat = userLog.coords.lat;
                auto lon = userLog.coords.lon;

                double minLat = std::min(box.topLeft.lat, box.bottomRight.lat);
                double maxLat = std::max(box.topLeft.lat, box.bottomRight.lat);
                double minLon = std::min(box.topLeft.lon, box.bottomRight.lon);
                double maxLon = std::max(box.topLeft.lon, box.bottomRight.lon);

                if (lat >= minLat && lat <= maxLat &&
                    lon >= minLon && lon <= maxLon) {
                    userData[user_id].insert({ userLog.timestamp, placeName });
                }

            }
        }
    }
    return userData;
}