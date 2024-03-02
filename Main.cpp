// main.cpp
#include "CSVParser.h"
#include <fstream>
#include <iostream>
#include <limits>

void menu(CSVParser &parser) {
  int choice;
  std::string courseCode;

  std::cout << "Welcome to the course planner." << std::endl;

  do {
    std::cout << "1. Load Data Structure." << std::endl;
    std::cout << "2. Print Course List." << std::endl;
    std::cout << "3. Print Course." << std::endl;
    std::cout << "9. Exit" << std::endl;
    std::cout << "What would you like to do? ";
    std::cin >> choice;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    switch (choice) {
    case 1: {
      std::string filename;
      std::cout << "Enter filename to load data: ";
      std::cin >> filename;
      parser = CSVParser(filename);
      std::cout << "Data loaded successfully!" << std::endl;
      break;
    }
    case 2: {
      std::cout << "Here is a sample schedule:" << std::endl;
      parser.display(); // Display to console
      // Write to sampleSchedule.txt
      std::ofstream sampleScheduleFile("sampleSchedule.txt");
      if (sampleScheduleFile.is_open()) {
        parser.display(sampleScheduleFile);
        sampleScheduleFile.close();
        std::cout << "Sample schedule written to sampleSchedule.txt."
                  << std::endl;
      } else {
        std::cerr << "Error opening sampleSchedule.txt for writing."
                  << std::endl;
      }
      break;
    }
    case 3: {
      std::cout << "What course do you want to know about? ";
      std::cin >> courseCode;
      const std::vector<std::string> &courseInfo = parser[courseCode];
      if (!courseInfo.empty()) {
        for (const auto &info : courseInfo) {
          std::cout << info << " ";
        }
        std::cout << std::endl;
        // Write course info to courseInfo.txt
        std::ofstream courseInfoFile("courseInfo.txt");
        if (courseInfoFile.is_open()) {
          for (const auto &info : courseInfo) {
            courseInfoFile << info << " ";
          }
          courseInfoFile.close();
          std::cout << "Course info written to courseInfo.txt." << std::endl;
        } else {
          std::cerr << "Error opening courseInfo.txt for writing." << std::endl;
        }
      } else {
        std::cout << "Course not found." << std::endl;
      }
      break;
    }
    case 9:
      std::cout << "Thank you for using the course planner!" << std::endl;
      break;
    default:
      std::cout << choice << " is not a valid option." << std::endl;
      break;
    }
  } while (choice != 9);
}

int main(int argc, char *argv[]) {
  CSVParser parser("");

  if (argc > 1) {
    parser = CSVParser(argv[1]);
  }

  menu(parser);
  return 0;
}
