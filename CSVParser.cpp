// CSVParser.cpp
#include "CSVParser.h"
#include <fstream>
/**
 * Constructor for CSVParser class.
 *
 * @param filename reference to the input file name
 *
 * @return void
 *
 * @throws none
 */
CSVParser::CSVParser(const std::string &filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Error opening file: " << filename << std::endl;
    return;
  }
  std::string line;
  while (std::getline(file, line)) {
    std::istringstream iss(line);
    std::string token, courseCode;
    std::vector<std::string> prerequisites;
    std::getline(iss, courseCode, ',');
    while (std::getline(iss, token, ',')) {
      prerequisites.push_back(token);
    }
    data.insert(courseCode, prerequisites);
  }
  file.close();
}
/**
 * Display the contents of the CSVParser to the specified output stream.
 *
 * @param out the output stream to display the contents to
 *
 * @return void
 *
 * @throws None
 */
void CSVParser::display(std::ostream &out) const {
  for (const auto &entry : data) {
    out << entry.first << ": ";
    for (const std::string &prerequisite : entry.second) {
      out << prerequisite << ", ";
    }
    out << std::endl;
  }
}

void CSVParser::sortCategory(const std::string &category) {
  std::cerr << "SortCategory: Not implemented for custom HashMap" << std::endl;
}

void CSVParser::displayUnits() const {
  std::cout << data.size() << " Units" << std::endl;
}

const std::vector<std::string> &
CSVParser::operator[](const std::string &courseCode) const {
  return data[courseCode];
}

std::vector<std::string> &CSVParser::operator[](const std::string &courseCode) {
  return data[courseCode];
}

size_t CSVParser::size() const { return data.size(); }
