#include "CryptoTestEasy.h"
#include "Ciphers.h"


static std::string randomWord() {
    static const std::vector<std::string> words = {
        "hello", "world", "crypto", "security", "algorithm", "programming",
        "computer", "science", "encryption", "main", "vector"
    };
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, words.size() - 1);
    return words[dist(gen)];
}

static std::string toLower(const std::string& s) {
    std::string res = s;
    for (char& c : res) c = tolower(c);
    return res;
}

void Test() {
    std::string original = randomWord();
    int shift = rand() % 25 + 1;
    std::string cipher = caesarEncrypt(original, shift);

    std::cout << "\n=== Task 1: Caesar cipher ===\n";
    std::cout << "Encrypted word: " << cipher << "\n";
    std::cout << "Write the decrypted word (or 'exit'): ";
    std::string answer = "";
    std::cin >> answer;

    if (answer == "exit" || answer == "Exit") return;
    if (toLower(answer) == original) {
        std::cout << "Right!\n";
    }
    else {
        std::cout << "False!\n";
    }
}

void TestTwo() {
    std::string original = randomWord();
    std::string cipher = atbash(original);

    std::cout << "\n=== Task 2: Atbash Cipher ===\n";
    std::cout << "Encrypted word: " << cipher << "\n";
    std::cout << "Write the encrypted word (or 'exit'): ";
    std::string answer = "";
    std::cin >> answer;

    if (answer == "exit") return;
    if (toLower(answer) == original) {
        std::cout << "Right!\n";
    }
    else {
        std::cout << "False!\n";
    }
}

void TestFree() {
    char key = 'K';
    std::string original = randomWord();
    std::string cipher = xorEncrypt(original, key);

    std::cout << "\n=== Task 3: XOR-encryption ===\n";
    std::cout << "Encrypted word (hex): ";
    for (unsigned char c : cipher) {
        std::cout << std::hex << (int)c << " ";
    }
    std::cout << "\nWrite decrypted word (or 'exit'): ";
    std::string answer;
    std::cin >> answer;

    if (answer == "exit" || answer == "Exit") return;
    if (toLower(answer) == original) {
        std::cout << "Right!\n";
    }
    else {
        std::cout << "False!\n";
    }
}

void TestFour() {
    std::string original = randomWord();
    std::string cipher = swapNibbles(original);

    std::cout << "\n=== Task 4: Notebook swapping ===\n";
    std::cout << "Encrypted word (hex): ";
    for (unsigned char c : cipher) {
        std::cout << std::hex << (int)c << " ";
    }
    std::cout << "\nWrite decrypted word (или 'exit'): ";
    std::string answer = "";
    std::cin >> answer;

    if (answer == "exit") return;
    if (toLower(answer) == original) {
        std::cout << "Right!\n";
    }
    else {
        std::cout << "False!\n";
    }
}

void TestFive() {
    char iv = 'I';
    std::string original = randomWord();
    std::string cipher = cbcEncrypt(original, iv);

    std::cout << "\n=== Task 5: Blocked cipher (CBC) ===\n";
    std::cout << "Encrypted word (hex): ";
    for (unsigned char c : cipher) {
        std::cout << std::hex << (int)c << " ";
    }
    std::cout << "\nWrite decrypted word (or 'exit'): ";
    std::string answer = "";
    std::cin >> answer;

    if (answer == "exit") return;
    if (toLower(answer) == original) {
        std::cout << "Right!\n";
    }
    else {
        std::cout << "False!\n";
    }
}



