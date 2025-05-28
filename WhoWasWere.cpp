#include "WhoWasWere.hpp"
#include "DataTypes.hpp"


using std::unordered_map;
using std::pair;
using std::vector;
using std::string;
using std::set;

WhoWasWere::WhoWasWere(unordered_map<int, vector<UserLogEntry>>& logs_, unordered_map<string, BoundingBox>& places_) : logs(logs_), places(places_) {

}

unordered_map<int, set<UserVisit>> WhoWasWere::getUserData() {
    for (const auto& [user_id, userLogs] : logs) {
        for (const auto& userLog : userLogs) {

            for (const auto& [placeName, box] : places) {
                const auto& [lat, lon] = userLog.coords;

                bool insideLat = (lat >= box.bottomRight.lat && lat <= box.topLeft.lat);
                bool insideLon = (lon <= box.bottomRight.lon && lon >= box.topLeft.lon);

                if (insideLat && insideLon) {
                    userData[user_id].insert({ userLog.timestamp, placeName });
                }
            }
        }
    }

    return userData;
}
