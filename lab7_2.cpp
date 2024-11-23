#include "header.h"

//2
void saveToFile(const std::string& filename, const std::vector<Book>& data) {
    std::ofstream file(filename); // ��������� ���� ��� ������

    // ���������, ������� �� ������� ����
    if (!file.is_open()) {
        std::cerr << "������ �������� ����� " << filename << std::endl;
        return;
    }

    // ���������� �����, ������ � ��� � �����
    for (const auto& i : data) {
        file << i.Author << '\n';
        file << i.Title << '\n';
        file << i.Year << '\n';
    }


    if (file.fail()) {
        std::cerr << "������" << filename << std::endl;
    }
    else {
        std::cout << "���� ��������: " << filename << std::endl;
    }
}



void loadFromFile(const std::string& filename, std::vector<Book>& outData) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "������ �������� �����" << filename << std::endl;
        return;
    }

    std::string l1; //�����
    std::string l2; //��������
    int l3; //���
    while (std::getline(file, l1) && std::getline(file,l2) && (file >> l3)) {
        file.ignore(); //���������� ������ ����� ������
        outData.push_back({ l1,l2,l3 });

    }

    if (file.bad()) {
        std::cerr << "������ " << filename << std::endl;
    }
    else {
        std::cout << "������ ��������� �� �����: " << filename << std::endl;
    }

}




int main() {
    setlocale(LC_ALL, "RU");
    std::vector<Book> books = {
        {"������", "������", 101010},
        {"��� ��������", "451� �� ����������", 1953},
        {"����", "������� ������", 18889}
    };

    saveToFile("books.txt", books);

    std::vector<Book> r;
    loadFromFile("books.txt", r);

    for (const auto& i : r) {
        std::cout << i.Author << " " << i.Title << " " << i.Year << std::endl;
    }


    return 0;
}