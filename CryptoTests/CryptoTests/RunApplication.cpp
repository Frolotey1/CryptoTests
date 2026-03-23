#include "RunApplication.h"
#include "Authorization.h"

void RunApplication() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    if (!Login()) {
        std::cout << "Exiting program" << std::endl;;
        return;
    }

    while (true) {
        std::cout << "\n=== CRYPTOGRAPHIC TRAINER ===\n";
        std::cout << "1) Easy training (random tasks)\n";
        std::cout << "2) Fixed tests (Russian tasks)\n";
        std::cout << "3) Sandbox (levels 2 and 3)\n";
        std::cout << "4) Return to authorization\n";
        std::cout << "0) Exit\n";
        std::cout << "Your choice:\n";
        std::string choice;
        std::cin >> choice;
        if (std::stoi(choice) == 0) break;
        if (!IsNumber(choice)) {
            std::cerr << "Not correct input!" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(1500));
            continue;
        }

        int opt = std::stoi(choice);
        choice.clear();

        if (opt == 1) {
            std::cout << "1) Choose task (1-5)\n";
            std::cout << "2) Random task\n";
            std::cout << "Your choice: ";
            std::cin >> choice;
            if (!IsNumber(choice)) {
                std::cerr << "Not correct input!" << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(1500));
                continue;
            }

            int sub = std::stoi(choice);
            choice.clear();

            if (sub == 1) {
                std::cout << "Enter task number (1-5):\n";
                std::cin >> choice;
                if (!IsNumber(choice)) {
                    std::cerr << "Not correct input!" << std::endl;
                    std::this_thread::sleep_for(std::chrono::milliseconds(1500));
                    continue;
                }

                switch (std::stoi(choice)) {
                case 1:
                    Test();
                    break;
                case 2:
                    TestTwo();
                    break;
                case 3:
                    TestFree();
                    break;
                case 4:
                    TestFour();
                    break;
                case 5:
                    TestFive();
                    break;
                default:
                    std::cerr << "Unexisted task" << std::endl;
                    break;
                }
            }
            else if (sub == 2) {
                int r = std::rand() % 5 + 1;
                std::cout << "Random task #" << r << "\n";
                switch (r) {
                case 1:
                    Test();
                    break;
                case 2:
                    TestTwo();
                    break;
                case 3:
                    TestFree();
                    break;
                case 4:
                    TestFour();
                    break;
                case 5:
                    TestFive();
                    break;
                }
            }
            else {
                std::cerr << "Not correct input!" << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(1500));
            }
        }
        else if (opt == 2) {
            std::cout << "Choose test (1-5): ";
            std::cin >> choice;
            if (!IsNumber(choice)) {
                std::cerr << "Not correct input!" << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(1500));
                continue;
            }

            switch(std::stoi(choice)) {
            case 1:
                test1();
                break;
            case 2:
                test2();
                break;
            case 3:
                test3();
                break;
            case 4:
                test4();
                break;
            case 5:
                test5();
                break;
            default:
                std::cerr << "Not correct input!" << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(1500));
                break;
            }
        }
        else if (opt == 3) {
            std::cout << "Choose level (2 or 3): ";
            std::cin >> choice;
            if (!IsNumber(choice)) {
                std::cerr << "Not correct input!" << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(1500));
                continue;
            }

            int lvl = std::stoi(choice);
            choice.clear();

            if (lvl == 2 || lvl == 3) {
                runLevel(lvl);
            }
            else {
                std::cerr << "Not correct input!" << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(1500));
            }
        } else if(opt == 4) {
            if(Login()) return;
            else RunApplication();
        }
        else {
            std::cerr << "Not correct input!" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(1500));
        }
    }
}
