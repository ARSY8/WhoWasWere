#include "FileReaderWriter.hpp"
#include "DataTypes.hpp"
#include <fstream>
#include <sstream>
#include <iomanip>


using std::unordered_map;
using std::pair;
using std::vector;
using std::string;
using std::set;

std::unordered_map<int, std::vector<UserLogEntry>> ReaderWriter::logsFileReader(const string& fileName) {
	
	std::unordered_map<int, std::vector<UserLogEntry>> logs;

	std::ifstream ifs(fileName);

	if (!ifs.is_open()) {
		throw std::runtime_error("Ну удалось открыть файл");
	}

	string line;

	while (std::getline(ifs, line)) {
		
		std::istringstream iss(line);

		string datePart, timePart;
		int user_id;
		double coordY, coordX;

		if (!(iss >> datePart >> timePart >> user_id >> coordY >> coordX)) {
			throw std::runtime_error("Не удалось прочитать строку");
		}

		if (coordY > 180 || coordY < 0 || coordX > 360 || coordX < 0) {
			continue;
		}

		string timestamp = datePart + ' ' + timePart;

		std::time_t t1 = parseTimestamp(timestamp);

		logs[user_id].push_back({ t1, {coordY, coordX} });
	}

	ifs.close();
	return logs;
}

std::unordered_map<std::string, BoundingBox> ReaderWriter::placesFileReader(const string& fileName) {
	std::unordered_map<std::string, BoundingBox> places;

	std::ifstream ifs(fileName);

	if (!ifs.is_open()) {
		throw std::runtime_error("Ну удалось открыть файл");
	}

	string line;

	while (std::getline(ifs, line)) {

		std::istringstream iss(line);

		string place;
		pair<double, double> coordsLT;
		pair<double, double> coordsRB;

		if (!(iss >> place >> coordsLT.first >> coordsLT.second >> coordsRB.first >> coordsRB.second)) {
			throw std::runtime_error("Не удалось прочитать строку");
		}

		if (coordsLT.first > 180 || coordsLT.first < 0 || coordsLT.second > 360 || coordsLT.second < 0) { continue; }
		if (coordsRB.first > 180 || coordsRB.first < 0 || coordsRB.second > 360 || coordsRB.second < 0) { continue; }

		places[place] = {{ coordsLT.first, coordsLT.second },{ coordsRB.first, coordsRB.second }};
	}

	ifs.close();
	return places;
}

void ReaderWriter::fileWriter(const std::unordered_map<int, std::set<UserVisit>>& userData) {
	for (const auto& [user_id, records] : userData) {
		std::string filename = "user_" + std::to_string(user_id) + ".txt";
		std::ofstream ofs(filename);
		if (!ofs.is_open()) {
			throw std::runtime_error("Не удалось открыть файл для записи: " + filename);
		}

		for (const auto& visit : records) {
			std::tm tm_snapshot;
#ifdef _WIN32
			localtime_s(&tm_snapshot, &visit.timestamp);
#else
			localtime_r(&visit.timestamp, &tm_snapshot);
#endif
			char timeStr[20];
			std::strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M", &tm_snapshot);

			ofs << timeStr << " " << visit.place << "\n";
		}

		ofs.close();
	}
}

std::time_t ReaderWriter::parseTimestamp(const std::string& timestamp) {
	std::tm tm{};
	std::istringstream iss(timestamp);

	iss >> std::get_time(&tm, "%Y-%m-%d %H:%M");
	if (iss.fail()) {
		throw std::runtime_error("Ошибка парсинга timestamp");
	}

	return std::mktime(&tm);
}