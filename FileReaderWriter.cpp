#include "FileReaderWriter.hpp"
#include <fstream>
#include <sstream>
#include <iomanip>


using std::unordered_map;
using std::pair;
using std::vector;
using std::string;
using std::set;

unordered_map<int, vector<pair<std::time_t, pair<double, double>>>> ReaderWriter::logsFileReader(const string& fileName) {
	
	unordered_map<int, vector<pair<std::time_t, pair<double, double>>>> logs;

	std::ifstream ifs(fileName);

	if (!ifs.is_open()) {
		throw std::runtime_error("Ну удалось открыть файл");
	}

	string line;

	while (std::getline(ifs, line)) {
		
		std::istringstream iss(line);

		string datePart, timePart;
		int user_id;
		double coordX, coordY;

		if (!(iss >> datePart >> timePart >> user_id >> coordX >> coordY)) {
			throw std::runtime_error("Не удалось прочитать строку");
		}

		string timestamp = datePart + ' ' + timePart;

		std::time_t t1 = parseTimestamp(timestamp);

		logs[user_id].push_back({ t1, {coordX, coordY} });
	}

	ifs.close();
	return logs;
}

unordered_map<string, pair<pair<double, double>, pair<double, double>>> ReaderWriter::placesFileReader(const string& fileName) {
	unordered_map<string, pair<pair<double, double>, pair<double, double>>> places;

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

		places[place] = { coordsLT, coordsRB };
	}

	ifs.close();
	return places;
}

void ReaderWriter::fileWriter(const unordered_map<int, set<pair<time_t, string>>>& userData) {
	for (const auto& [user_id, records] : userData) {
		std::string filename = "user_" + std::to_string(user_id) + ".txt";
		std::ofstream ofs(filename);
		if (!ofs.is_open()) {
			throw std::runtime_error("Не удалось открыть файл для записи: " + filename);
		}

		for (const auto& [timestamp, place] : records) {
			std::tm tm_snapshot;
#ifdef _WIN32
			localtime_s(&tm_snapshot, &timestamp);
#else
			localtime_r(&timestamp, &tm_snapshot);
#endif

			char timeStr[20];
			std::strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M", &tm_snapshot);

			ofs << timeStr << " " << place << "\n";
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

	tm.tm_isdst = -1;
	return std::mktime(&tm);
}