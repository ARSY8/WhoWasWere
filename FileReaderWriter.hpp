#include <unordered_map>
#include <string>
#include <vector>
#include <ctime>
#include <utility>
#include <set>
#include "DataTypes.hpp"



class ReaderWriter final {
	ReaderWriter() = delete;
	~ReaderWriter() = delete;

public:
	static std::unordered_map<int, std::vector<UserLogEntry>> logsFileReader(const std::string& fileName);

	static std::unordered_map<std::string, BoundingBox> placesFileReader(const std::string& fileName);

	static void fileWriter(const std::unordered_map<int, std::set<UserVisit>>& userData);

private:
	static std::time_t parseTimestamp(const std::string& timestamp);
};