#pragma once
#include <unordered_map>
#include <string>
#include <vector>
#include <ctime>
#include <set>

//unordered_map<user_id, pair<timestamp, pair<coords>>>
//unordered_map<places_name, pair<pair<coords_lt>, pair<coords_rb>>>
// ->
//unordered_map<user_id, set<pair<timestamp, places_name>>>

class WhoWasWere final {
	std::unordered_map<int, std::vector<std::pair<std::time_t, std::pair<double, double>>>>& logs;
	std::unordered_map<std::string, std::pair<std::pair<double, double>, std::pair<double, double>>>& places;
	std::unordered_map<int, std::set<std::pair<std::time_t, std::string>>> userData;

	struct hash_latlon {
		std::size_t operator()(const std::pair<int, int>& p) const {
			return std::hash<int>{}(p.first) ^ (std::hash<int>{}(p.second) << 1);
		}
	};

	double scale = 0.1;

	std::unordered_map<std::pair<int, int>, std::set<std::string>, hash_latlon> gridIndex;

public:
	WhoWasWere(std::unordered_map<int, std::vector<std::pair<std::time_t, std::pair<double, double>>>>& logs_,
			   std::unordered_map<std::string, std::pair<std::pair<double, double>, std::pair<double, double>>>& places_);

	std::unordered_map<int, std::set<std::pair<std::time_t, std::string>>> getUserData();

private:
	std::pair<int, int> getGridCell(double lat, double lon) const;
	void fillGridIndex();
};

