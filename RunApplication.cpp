#include "RunApplication.h"
#include "Authorization.h"

void RunApplication() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    if (!Login()) {
        std::cout << "Exiting program.\n";
        return;
    }

    while (true) {
        std::cout << "\n=== CRYPTOGRAPHIC TRAINER ===\n";
        std::cout << "1 – Easy training (random tasks)\n";
        std::cout << "2 – Fixed tests (Russian tasks)\n";
        std::cout << "3 – Sandbox (levels 2 and 3)\n";
        std::cout << "0 – Exit\n";
        std::cout << "Your choice: ";
        std::string choice;
        Getline(choice);
        if (choice == "0") break;
        if (!IsNumber(choice)) {
            Err();
            continue;
        }
        int opt = std::stoi(choice);

        if (opt == 1) {
            std::cout << "1 – Choose task (1-5)\n";
            std::cout << "2 – Random task\n";
            std::cout << "Your choice: ";
            Getline(choice);
            if (!IsNumber(choice)) {
                Err();
                continue;
            }
            int sub = std::stoi(choice);
            if (sub == 1) {
                std::cout << "Enter task number (1-5): ";
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
                std::cout << "Random task #" << r << "\n";
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
            std::cout << "Choose test (1-5): ";
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
            std::cout << "Choose level (2 or 3): ";
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