#include "header.h"

//1.1
void saveToFile(const std::string& filename, const std::vector<std::string>& data) {
    std::ofstream file(filename);   // открываем файл

    if (!file.is_open()) {    // проверяем, удалось ли открыть файл
        std::cerr << "Ошибка открытия файла " << filename << std::endl;
        return; // выходим из функции, если открыть файл не получилось
    }

    // записываем данные в файл
    for (const std::string& line : data) {
        file << line << '\n'; // записываем каждую строку и переносим
    }

    // проверка,удалось ли записать файл
    if (file.fail()) {
        std::cerr << "Ошибка " << filename << std::endl;
    }
    else {
        std::cout << "Файл сохранен: " << filename << std::endl;
    }

}



//1.2
void loadFromFile(const std::string& filename, std::vector<std::string>& outData) {
    std::ifstream file(filename);  // открываем файл для чтения

    // проверяем, открылся ли файл
    if (!file.is_open()) {
        std::cerr << "Ошибка открытия файла " << filename << std::endl;
        return; // выходим, если файл не открылся
    }

    std::string line;   // читаем файл построчно
    while (std::getline(file, line)) {
        outData.push_back(line);       // добавляем строку в вектор
    }

    // проверка на ошибки
    if (file.bad()) {
        std::cerr << "Ошибка " << filename << std::endl;
    }
    else {
        std::cout << "Данные выгружены из файла: " << filename << std::endl;
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