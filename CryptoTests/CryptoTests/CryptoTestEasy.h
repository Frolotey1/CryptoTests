#ifndef CRYPTO_TEST_EASY_H
#define CRYPTO_TEST_EASY_H
#include "Header.h"


inline void Getline(std::string& str) {
    std::getline(std::cin, str);
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(365000, '\n');
    }
}

inline void Err(int time = 1500) {
    std::cout << "Некорректный ввод!\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(1500));
}

inline bool IsNumber(const std::string& str) {
    if (str.empty() || str.size() >= 10) return false;
    for (size_t i = 0; i < str.size(); ++i) {
        if (!std::isdigit(str[i],std::locale(""))) return false;
    }
    return true;
}

void Test();       // Цезарь
void TestTwo();    // Атбаш
void TestFree();   // XOR
void TestFour();   // Перестановка тетрад
void TestFive();   // CBC

#endif
