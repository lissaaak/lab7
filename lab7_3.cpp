#include "header.h"


//3.1
void saveToFile(const std::string& filename, const Groups& groups) {
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Ошибка открытия файла " << filename << std::endl;
        return;
    }

    for (auto& i : groups) { // проходим по группам
        file << "Группа:" << i.first << std::endl;

        for (auto& j : i.second) { // проходим по студентам
            file << "Имя:" << j.Name << std::endl;
            file << "Курс:" << j.Year << std::endl;

            file << "Зачётная книжка:" << std::endl;
            for (auto& r : j.RecordBook) { // проходим по предметам
                file << "Предмет:" << r.first << ", Оценка:" << r.second << std::endl;
            }
        }
    }

    file.close();
}



Score strl(const std::string& str) {  // преобразование строки в оценку
    if (str == "2") return Unsatisfactorily;
    if (str == "3") return Satisfactorily;
    if (str == "4") return Good;
    if (str == "5") return Excellent;
}



//3.2
void loadFromFile(const std::string& filename, Groups& outGroups) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Ошибка открытия файла" << std::endl;
        return;
    }

    std::string l;
    std::string group;
    Student student;

    while (std::getline(file, l)) {
        if (l.empty()) continue;  // если строка l пустая, то пропускаем и идем дальше

        if (l.find("Группа:") == 0) {  // если l начинается со строки Группа:, то l извлекает подстроку начиная с 7 символа
            group = l.substr(7);
        }
        else if (l.find("Имя:") == 0) {
            student.Name = l.substr(4);  // извлекаем имя
        }
        else if (l.find("Курс:") == 0) {
            student.Year = std::stoi(l.substr(5));  // извлекаем курс
        }
        else if (l.find("Предмет:") == 0) {  // Чтение предметов и оценок
            std::stringstream ss(l.substr(8)); //разбираем подстроку после слова "Предмет:" , начиная с 8 индекса
            std::string subject, gradeStr; // вводим переменные предмет и оценка
            std::getline(ss, subject, ','); // извлекаем из ss строку, которая хранит в себе название предмета
            std::getline(ss, gradeStr);  // извлекаем строку с оценкой
            gradeStr = gradeStr.substr(8);  // извлекаем оценку после слова "Оценка:"
            Score grade = strl(gradeStr);  // преобразуем строку в оценку
            student.RecordBook[subject] = grade;  // добавляем полученную запись студенту
        }

        if (l.find("Зачётная книжка:") == 0) {
            outGroups[group].push_back(student);  // добавляем студента в группу
            student = Student();  // сбрасываем текущего студента для следующего
        }
    }

    file.close();
}

int main() {
    setlocale(LC_ALL, "RU");

    Groups groups = {
        {"Группа 1", {
            {"Петя", 1, {{"Математика", Excellent}, {"Физика", Good}}},
            {"Коля", 2, {{"Химия", Satisfactorily}, {"Биология", Good}}}
        }},
        {"Группа 2", {
            {"Влад", 3, {{"История", Good}, {"География", Excellent}}},
            {"Алиса", 4, {{"Физика", Unsatisfactorily}, {"Математика", Satisfactorily}}}
        }}
    };

    saveToFile("groups.txt", groups);

    Groups g;
    loadFromFile("groups.txt", g);


    for (const auto& i : g) {
        std::cout << "Группа: " << i.first << std::endl;
        for (const auto& student : i.second) {
            std::cout << "Имя: " << student.Name << " Курс: " << student.Year << std::endl;
            std::cout << "Зачётная книжка:" << std::endl;
            for (const auto& record : student.RecordBook) {
                std::cout << "Предмет: " << record.first << " Оценка:" << record.second << std::endl;
            }
            std::cout << " " << std::endl;
        }
        std::cout << " " << std::endl;
    }

    return 0;
}