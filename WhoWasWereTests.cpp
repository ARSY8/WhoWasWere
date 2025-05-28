#include <gtest/gtest.h>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <unordered_map>
#include <filesystem>
#include "FileReaderWriter.hpp"
#include "WhoWasWere.hpp"

namespace fs = std::filesystem;

class FullProgramTest : public ::testing::Test {
protected:
    std::string logsFile = "test_logs.txt";
    std::string placesFile = "test_places.txt";
    std::string outputFile1 = "user_1.txt";
    std::string outputFile2 = "user_2.txt";
    std::string outputFile3 = "user_3.txt";

    void SetUp() override {
        std::ofstream logs(logsFile);
        logs << "2025-01-01 12:00 1 55.7 37.6\n"; //москва
        logs << "2025-01-01 13:00 1 59.9 30.3\n"; //спб
        logs << "2025-01-01 13:30 2 50.4 30.5\n"; //киев
        logs << "2025-01-01 14:00 2 52.5 13.4\n"; //берлин
        logs << "2025-01-01 14:30 3 48.8 2.3\n";   //париж
        logs << "2025-01-01 15:00 3 35.6 139.7\n"; //токио
        logs.close();

        std::ofstream places(placesFile);
        places << "Moscow 55.9 37.9 55.4 37.5\n";
        places << "SPB 59.9 30.4 59.9 30.3\n";
        places << "Kiev 50.6 30.7 50.3 30.4\n";
        places << "Berlin 52.7 13.7 52.4 13.4\n";
        places << "Paris 48.9 2.4 48.7 2.2\n";
        places << "Tokyo 35.6 139.7 35.4 139.6\n";
        places.close();
    }

    void TearDown() override {
        fs::remove(logsFile);
        fs::remove(placesFile);
        fs::remove(outputFile1);
        fs::remove(outputFile2);
        fs::remove(outputFile3);
    }

    std::vector<std::string> readFileLines(const std::string& filename) {
        std::ifstream file(filename);
        std::vector<std::string> lines;
        std::string line;
        while (std::getline(file, line)) {
            lines.push_back(line);
        }
        return lines;
    }
};

TEST_F(FullProgramTest, CorrectOutput) {
    auto logs = ReaderWriter::logsFileReader(logsFile);
    auto places = ReaderWriter::placesFileReader(placesFile);

    WhoWasWere who(logs, places);
    auto result = who.getUserData();
    ReaderWriter::fileWriter(result);

    auto actual1 = readFileLines(outputFile1);
    std::vector<std::string> expected1 = {
        "2025-01-01 12:00 Moscow",
        "2025-01-01 13:00 SPB"
    };

    auto actual2 = readFileLines(outputFile2);
    std::vector<std::string> expected2 = {
        "2025-01-01 13:30 Kiev",
        "2025-01-01 14:00 Berlin"
    };
    
    auto actual3 = readFileLines(outputFile3);
    std::vector<std::string> expected3 = {
        "2025-01-01 14:30 Paris",
        "2025-01-01 15:00 Tokyo"
    };

    ASSERT_EQ(actual1.size(), expected1.size());
    for (size_t i = 0; i < expected1.size(); ++i) {
        EXPECT_EQ(actual1[i], expected1[i]);
    }

    ASSERT_EQ(actual2.size(), expected2.size());
    for (size_t i = 0; i < expected2.size(); ++i) {
        EXPECT_EQ(actual2[i], expected2[i]);
    }

    ASSERT_EQ(actual3.size(), expected3.size());
    for (size_t i = 0; i < expected3.size(); ++i) {
        EXPECT_EQ(actual3[i], expected3[i]);
    }
}
