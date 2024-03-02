// CSVParser.h
#ifndef CSVPARSER_H
#define CSVPARSER_H

#include "HashMap.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class CSVParser {
private:
  HashMap<std::string, std::vector<std::string>> data;

public:
  CSVParser(const std::string &filename);
  void display(std::ostream &out = std::cout) const;
  void sortCategory(const std::string &category);
  void displayUnits() const;
  const std::vector<std::string> &
  operator[](const std::string &courseCode) const;
  std::vector<std::string> &operator[](const std::string &courseCode);
  size_t size() const;
};

#endif // CSVPARSER_H
