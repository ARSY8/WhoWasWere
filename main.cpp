#include <iostream>
#include <unordered_map>
#include <vector>
#include <set>
#include <string>
#include <ctime>
#include "FileReaderWriter.hpp"
#include "WhoWasWere.hpp"
#include "DataTypes.hpp"


int main() {
    try {
        auto logs = ReaderWriter::logsFileReader("logs.txt");
        auto places = ReaderWriter::placesFileReader("places.txt");

        WhoWasWere whoWasWere(logs, places);

        auto userData = whoWasWere.getUserData();

        ReaderWriter::fileWriter(userData);

        std::cout << "Запись файлов завершена успешно.\n";
    }
    catch (const std::exception& ex) {
        std::cerr << "Ошибка: " << ex.what() << "\n";
        return 1;
    }
    return 0;
}