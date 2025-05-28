#pragma once
#include <unordered_map>
#include <string>
#include <vector>
#include <ctime>
#include <set>
#include "DataTypes.hpp"

//unordered_map<user_id, pair<timestamp, pair<coords>>>
//unordered_map<places_name, pair<pair<coords_lt>, pair<coords_rb>>>
// ->
//unordered_map<user_id, set<pair<timestamp, places_name>>>

class WhoWasWere final {
	std::unordered_map<int, std::vector<UserLogEntry>>& logs;
	std::unordered_map<std::string, BoundingBox>& places;
	std::unordered_map<int, std::set<UserVisit>> userData;

public:
	WhoWasWere(std::unordered_map<int, std::vector<UserLogEntry>>& logs_, std::unordered_map<std::string, BoundingBox>& places_);

	std::unordered_map<int, std::set<UserVisit>> getUserData();
private:
};
