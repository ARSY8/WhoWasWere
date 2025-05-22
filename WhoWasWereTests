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
    std::string outputFile = "user_1.txt";

    void SetUp() override {
        std::ofstream logs(logsFile);
        logs << "2025-01-01 12:00 1 55.75 37.62\n"; //moscow
        logs << "2025-01-01 13:00 1 59.94 30.31\n"; //spb
        logs.close();

        std::ofstream places(placesFile);
        places << "Moscow 55.70 37.60 55.80 37.70\n";
        places << "SPB 59.90 30.20 59.95 30.35\n";
        places.close();
    }

    void TearDown() override {
        fs::remove(logsFile);
        fs::remove(placesFile);
        fs::remove(outputFile);
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

TEST_F(FullProgramTest, ProgramExecutionProducesCorrectOutput) {
    auto logs = ReaderWriter::logsFileReader(logsFile);
    auto places = ReaderWriter::placesFileReader(placesFile);

    WhoWasWere who(logs, places);
    auto result = who.getUserData();
    ReaderWriter::fileWriter(result);

    auto actual = readFileLines(outputFile);
    std::vector<std::string> expected = {
        "2025-01-01 12:00 Moscow",
        "2025-01-01 13:00 SPB"
    };

    ASSERT_EQ(actual.size(), expected.size());
    for (size_t i = 0; i < expected.size(); ++i) {
        EXPECT_EQ(actual[i], expected[i]);
    }
}
