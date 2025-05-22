#include <unordered_map>
#include <string>
#include <vector>
#include <ctime>
#include <utility>
#include <set>



class ReaderWriter final {
	ReaderWriter() = delete;
	~ReaderWriter() = delete;
public:
	static std::unordered_map<int, std::vector<std::pair<std::time_t, std::pair<double, double>>>> logsFileReader(const std::string& fileName);

	static std::unordered_map<std::string, std::pair<std::pair<double, double>, std::pair<double, double>>> placesFileReader(const std::string& fileName);

	static void fileWriter(const std::unordered_map<int, std::set<std::pair<std::time_t, std::string>>>& userData);

private:
	static std::time_t parseTimestamp(const std::string& timestamp);
};