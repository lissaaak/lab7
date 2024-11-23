#include "header.h"

//1.1
void saveToFile(const std::string& filename, const std::vector<std::string>& data) {
    std::ofstream file(filename);   // ��������� ����

    if (!file.is_open()) {    // ���������, ������� �� ������� ����
        std::cerr << "������ �������� ����� " << filename << std::endl;
        return; // ������� �� �������, ���� ������� ���� �� ����������
    }

    // ���������� ������ � ����
    for (const std::string& line : data) {
        file << line << '\n'; // ���������� ������ ������ � ���������
    }

    // ��������,������� �� �������� ����
    if (file.fail()) {
        std::cerr << "������ " << filename << std::endl;
    }
    else {
        std::cout << "���� ��������: " << filename << std::endl;
    }

}



//1.2
void loadFromFile(const std::string& filename, std::vector<std::string>& outData) {
    std::ifstream file(filename);  // ��������� ���� ��� ������

    // ���������, �������� �� ����
    if (!file.is_open()) {
        std::cerr << "������ �������� ����� " << filename << std::endl;
        return; // �������, ���� ���� �� ��������
    }

    std::string line;   // ������ ���� ���������
    while (std::getline(file, line)) {
        outData.push_back(line);       // ��������� ������ � ������
    }

    // �������� �� ������
    if (file.bad()) {
        std::cerr << "������ " << filename << std::endl;
    }
    else {
        std::cout << "������ ��������� �� �����: " << filename << std::endl;
    }
}

int main() {
    setlocale(LC_ALL, "RU");

    std::vector<std::string> data1 = { "hi", "odkdk.", "DJDKDMDK" };
    std::string filename = "output.txt";

    saveToFile(filename, data1);

    std::vector<std::string> data2;

    loadFromFile(filename, data2);

    for (const auto& line : data2) {
        std::cout << line << std::endl;
    }

    return 0;
}