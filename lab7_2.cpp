#include "header.h"

//2
void saveToFile(const std::string& filename, const std::vector<Book>& data) {
    std::ofstream file(filename); // открываем файл для записи

    // проверяем, удалось ли открыть файл
    if (!file.is_open()) {
        std::cerr << "Ошибка открытия файла " << filename << std::endl;
        return;
    }

    // записываем книгу, автора и год в файле
    for (const auto& i : data) {
        file << i.Author << '\n';
        file << i.Title << '\n';
        file << i.Year << '\n';
    }


    if (file.fail()) {
        std::cerr << "Ошибка" << filename << std::endl;
    }
    else {
        std::cout << "Файл сохранен: " << filename << std::endl;
    }
}



void loadFromFile(const std::string& filename, std::vector<Book>& outData) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Ошибка открытия файла" << filename << std::endl;
        return;
    }

    std::string l1; //автор
    std::string l2; //название
    int l3; //год
    while (std::getline(file, l1) && std::getline(file,l2) && (file >> l3)) {
        file.ignore(); //пропускаем символ новой строки
        outData.push_back({ l1,l2,l3 });

    }

    if (file.bad()) {
        std::cerr << "Ошибка " << filename << std::endl;
    }
    else {
        std::cout << "Данные выгружены из файла: " << filename << std::endl;
    }

}




int main() {
    setlocale(LC_ALL, "RU");
    std::vector<Book> books = {
        {"Пушкин", "Онегин", 101010},
        {"Рэй Брэдбери", "451° по Фаренгейту", 1953},
        {"Лепс", "Евгений Онегин", 18889}
    };

    saveToFile("books.txt", books);

    std::vector<Book> r;
    loadFromFile("books.txt", r);

    for (const auto& i : r) {
        std::cout << i.Author << " " << i.Title << " " << i.Year << std::endl;
    }


    return 0;
}