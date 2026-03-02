#include "RunApplication.h"
#include "Authorization.h"

void RunApplication() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    if (!Login()) {
        std::cout << "Выход из программы.\n";
        return;
    }

    while (true) {
        std::cout << "\n=== КРИПТОГРАФИЧЕСКИЙ ТРЕНАЖЁР ===\n";
        std::cout << "1 – Лёгкий тренинг (случайные задачи)\n";
        std::cout << "2 – Фиксированные тесты (русские)\n";
        std::cout << "3 – Песочница (уровни 2 и 3)\n";
        std::cout << "0 – Выход\n";
        std::cout << "Ваш выбор: ";
        std::string choice;
        Getline(choice);
        if (choice == "0") break;
        if (!IsNumber(choice)) {
            Err();
            continue;
        }
        int opt = std::stoi(choice);

        if (opt == 1) {
            std::cout << "1 – Выбрать задачу (1-5)\n";
            std::cout << "2 – Случайная задача\n";
            std::cout << "Ваш выбор: ";
            Getline(choice);
            if (!IsNumber(choice)) {
                Err();
                continue;
            }
            int sub = std::stoi(choice);
            if (sub == 1) {
                std::cout << "Введите номер задачи (1-5): ";
                Getline(choice);
                if (!IsNumber(choice)) {
                    Err();
                    continue;
                }
                int task = std::stoi(choice);
                if (task < 1 || task > 5) {
                    Err();
                    continue;
                }
                switch (task) {
                case 1: Test(); break;
                case 2: TestTwo(); break;
                case 3: TestFree(); break;
                case 4: TestFour(); break;
                case 5: TestFive(); break;
                }
            }
            else if (sub == 2) {
                int r = std::rand() % 5 + 1;
                std::cout << "Случайная задача №" << r << "\n";
                switch (r) {
                case 1: Test(); break;
                case 2: TestTwo(); break;
                case 3: TestFree(); break;
                case 4: TestFour(); break;
                case 5: TestFive(); break;
                }
            }
            else {
                Err();
            }
        }
        else if (opt == 2) {
            std::cout << "Выберите тест (1-5): ";
            Getline(choice);
            if (!IsNumber(choice)) {
                Err();
                continue;
            }
            int t = std::stoi(choice);
            if (t == 1) test1();
            else if (t == 2) test2();
            else if (t == 3) test3();
            else if (t == 4) test4();
            else if (t == 5) test5();
            else Err();
        }
        else if (opt == 3) {
            std::cout << "Выберите уровень (2 или 3): ";
            Getline(choice);
            if (!IsNumber(choice)) {
                Err();
                continue;
            }
            int lvl = std::stoi(choice);
            if (lvl == 2 || lvl == 3) {
                runLevel(lvl);
            }
            else {
                Err();
            }
        }

        else {
            Err();
        }
    }
}

