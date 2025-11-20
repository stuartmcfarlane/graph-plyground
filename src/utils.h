#include <vector>
#include <string>

std::vector<std::string> readFileLines(const std::string filename);

std::vector<std::string> parseCommaSeparated(const std::string str);

std::vector<int> toInts(std::vector<std::string> ss);
