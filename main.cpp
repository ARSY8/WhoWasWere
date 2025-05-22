#include <iostream>
#include <unordered_map>
#include <vector>
#include <set>
#include <string>
#include <ctime>
#include "FileReaderWriter.hpp"
#include "WhoWasWere.hpp"


int main() {
    try {
        // Читаем логи и места из файлов
        auto logs = ReaderWriter::logsFileReader("logs.txt");
        auto places = ReaderWriter::placesFileReader("places.txt");

        // Создаём WhoWasWere, чтобы сопоставить координаты с местами
        WhoWasWere whoWasWere(logs, places);

        // Получаем данные с таймштампами и названиями мест для каждого пользователя
        auto userData = whoWasWere.getUserData();

        // Записываем результаты в файлы для каждого пользователя
        ReaderWriter::fileWriter(userData);

        std::cout << "Запись файлов завершена успешно.\n";
    }
    catch (const std::exception& ex) {
        std::cerr << "Ошибка: " << ex.what() << "\n";
        return 1;
    }
    return 0;
}