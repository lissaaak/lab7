#include "header.h"


//3.1
void saveToFile(const std::string& filename, const Groups& groups) {
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cerr << "������ �������� ����� " << filename << std::endl;
        return;
    }

    for (auto& i : groups) { // �������� �� �������
        file << "������:" << i.first << std::endl;

        for (auto& j : i.second) { // �������� �� ���������
            file << "���:" << j.Name << std::endl;
            file << "����:" << j.Year << std::endl;

            file << "�������� ������:" << std::endl;
            for (auto& r : j.RecordBook) { // �������� �� ���������
                file << "�������:" << r.first << ", ������:" << r.second << std::endl;
            }
        }
    }

    file.close();
}



Score strl(const std::string& str) {  // �������������� ������ � ������
    if (str == "2") return Unsatisfactorily;
    if (str == "3") return Satisfactorily;
    if (str == "4") return Good;
    if (str == "5") return Excellent;
}



//3.2
void loadFromFile(const std::string& filename, Groups& outGroups) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "������ �������� �����" << std::endl;
        return;
    }

    std::string l;
    std::string group;
    Student student;

    while (std::getline(file, l)) {
        if (l.empty()) continue;  // ���� ������ l ������, �� ���������� � ���� ������

        if (l.find("������:") == 0) {  // ���� l ���������� �� ������ ������:, �� l ��������� ��������� ������� � 7 �������
            group = l.substr(7);
        }
        else if (l.find("���:") == 0) {
            student.Name = l.substr(4);  // ��������� ���
        }
        else if (l.find("����:") == 0) {
            student.Year = std::stoi(l.substr(5));  // ��������� ����
        }
        else if (l.find("�������:") == 0) {  // ������ ��������� � ������
            std::stringstream ss(l.substr(8)); //��������� ��������� ����� ����� "�������:" , ������� � 8 �������
            std::string subject, gradeStr; // ������ ���������� ������� � ������
            std::getline(ss, subject, ','); // ��������� �� ss ������, ������� ������ � ���� �������� ��������
            std::getline(ss, gradeStr);  // ��������� ������ � �������
            gradeStr = gradeStr.substr(8);  // ��������� ������ ����� ����� "������:"
            Score grade = strl(gradeStr);  // ����������� ������ � ������
            student.RecordBook[subject] = grade;  // ��������� ���������� ������ ��������
        }

        if (l.find("�������� ������:") == 0) {
            outGroups[group].push_back(student);  // ��������� �������� � ������
            student = Student();  // ���������� �������� �������� ��� ����������
        }
    }

    file.close();
}

int main() {
    setlocale(LC_ALL, "RU");

    Groups groups = {
        {"������ 1", {
            {"����", 1, {{"����������", Excellent}, {"������", Good}}},
            {"����", 2, {{"�����", Satisfactorily}, {"��������", Good}}}
        }},
        {"������ 2", {
            {"����", 3, {{"�������", Good}, {"���������", Excellent}}},
            {"�����", 4, {{"������", Unsatisfactorily}, {"����������", Satisfactorily}}}
        }}
    };

    saveToFile("groups.txt", groups);

    Groups g;
    loadFromFile("groups.txt", g);


    for (const auto& i : g) {
        std::cout << "������: " << i.first << std::endl;
        for (const auto& student : i.second) {
            std::cout << "���: " << student.Name << " ����: " << student.Year << std::endl;
            std::cout << "�������� ������:" << std::endl;
            for (const auto& record : student.RecordBook) {
                std::cout << "�������: " << record.first << " ������:" << record.second << std::endl;
            }
            std::cout << " " << std::endl;
        }
        std::cout << " " << std::endl;
    }

    return 0;
}