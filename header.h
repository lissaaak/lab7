#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <sstream>




struct Book
{
    std::string Author;
    std::string Title;
    int Year;
};
enum Score {
    Unsatisfactorily = 2,
    Satisfactorily,
    Good,
    Excellent
};

struct Student {
    std::string Name;
    int Year;
    std::map<std::string, Score> RecordBook;
};

using Groups = std::map<std::string, std::vector<Student>>;


void saveToFile(const std::string& filename, const std::vector<std::string>& data);
void loadFromFile(const std::string& filename, std::vector<std::string>& outData);
void saveToFile(const std::string& filename, const std::vector<Book>& data);
void loadFromFile(const std::string& filename, std::vector<Book>& outData);
void saveToFile(const std::string& filename, const Groups& groups);
void loadFromFile(const std::string& filename, Groups& outGroups);
