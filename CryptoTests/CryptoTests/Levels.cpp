#include "Levels.h"
#include "CryptoTestEasy.h"
#include "Ciphers.h"

static std::vector<std::string> encryptedMessages;

static void printHex(const std::string& s) {
    for (unsigned char c : s) {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)c << " ";
    }
    std::cout << std::dec;
}

static void printStored() {
    if (encryptedMessages.empty()) {
        std::cerr << "No saved encrypted messages.\n";
        return;
    }
    std::cout << "Saved encrypted messages:\n";
    for (size_t i = 0; i < encryptedMessages.size(); ++i) {
        std::cout << i + 1 << ": ";
        printHex(encryptedMessages[i]);
        std::cout << "\n";
    }
}

static std::string getInput(const std::string& prompt) {
    std::cout << prompt;
    std::string s;
    std::getline(std::cin,s);
    return s;
}

static int getChoice(const std::string& prompt, int min, int max) {
    while (true) {
        std::string s = getInput(prompt);
        if (s == "exit" || s == "Exit") return -1;
        if (!IsNumber(s)) {
            std::cerr << "Not correct input!\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(1500));
            continue;
        }
        int val = std::stoi(s);
        if (val >= min && val <= max) return val;
        std::cerr << "Not correct input!" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1500));
    }
}

static void caesarHandler(int level) {
    int action = getChoice("1 � encrypt, 2 � decrypt, 0 � back: ", 0, 2);
    if (action == 0) return;
    if (action == 1) {
        std::string text = getInput("Enter text: ");
        int shift = (level == 2) ? 3 : getChoice("Enter shift (1-25): ", 1, 25);
        if (shift == -1) return;
        std::string enc = caesarEncrypt(text, shift);
        encryptedMessages.push_back(enc);
        std::cout << "Encrypted: ";
        printHex(enc);
        std::cout << " (index " << encryptedMessages.size() << ")\n";
    }
    else {
        if (encryptedMessages.empty()) {
            std::cout << "No saved messages.\n";
            return;
        }
        printStored();
        int idx = getChoice("Choose index: ", 1, encryptedMessages.size());
        if (idx == -1) return;
        int shift = (level == 2) ? 3 : getChoice("Enter shift (1-25): ", 1, 25);
        if (shift == -1) return;
        std::string dec = caesarDecrypt(encryptedMessages[idx - 1], shift);
        std::cout << "Decrypted: " << dec << "\n";
    }
}

static void atbashHandler(int level) {
    int action = getChoice("1 � encrypt, 2 � decrypt, 0 � back: ", 0, 2);
    if (action == 0) return;
    if (action == 1) {
        std::string text = getInput("Enter text: ");
        std::string enc = atbash(text);
        encryptedMessages.push_back(enc);
        std::cout << "Encrypted: ";
        printHex(enc);
        std::cout << " (index " << encryptedMessages.size() << ")\n";
    }
    else {
        if (encryptedMessages.empty()) {
            std::cout << "No saved messages.\n";
            return;
        }
        printStored();
        int idx = getChoice("Choose index: ", 1, encryptedMessages.size());
        if (idx == -1) return;
        std::string dec = atbash(encryptedMessages[idx - 1]);
        std::cout << "Decrypted: " << dec << "\n";
    }
}

static void xorHandler(int level) {
    int action = getChoice("1 � encrypt, 2 � decrypt, 0 � back: ", 0, 2);
    if (action == 0) return;
    if (action == 1) {
        std::string text = getInput("Enter text: ");
        std::string enc;
        if (level == 2) {
            char key = 'K';
            enc = xorEncrypt(text, key);
        }
        else {
            std::string key = getInput("Enter key string: ");
            enc = text;
            for (size_t i = 0; i < text.size(); ++i)
                enc[i] = text[i] ^ key[i % key.size()];
        }
        encryptedMessages.push_back(enc);
        std::cout << "Encrypted: ";
        printHex(enc);
        std::cout << " (index " << encryptedMessages.size() << ")\n";
    }
    else {
        if (encryptedMessages.empty()) {
            std::cout << "No saved messages.\n";
            return;
        }
        printStored();
        int idx = getChoice("Choose index: ", 1, encryptedMessages.size());
        if (idx == -1) return;
        std::string cipher = encryptedMessages[idx - 1];
        std::string dec;
        if (level == 2) {
            char key = 'K';
            dec = xorDecrypt(cipher, key);
        }
        else {
            std::string key = getInput("Enter key string: ");
            dec = cipher;
            for (size_t i = 0; i < cipher.size(); ++i)
                dec[i] = cipher[i] ^ key[i % key.size()];
        }
        std::cout << "Decrypted: " << dec << "\n";
    }
}

static void swapHandler(int level) {
    int action = getChoice("1 � encrypt, 2 � decrypt, 0 � back: ", 0, 2);
    if (action == 0) return;
    if (action == 1) {
        std::string text = getInput("Enter text: ");
        std::string enc = swapNibbles(text);
        encryptedMessages.push_back(enc);
        std::cout << "Encrypted: ";
        printHex(enc);
        std::cout << " (index " << encryptedMessages.size() << ")\n";
    }
    else {
        if (encryptedMessages.empty()) {
            std::cout << "No saved messages.\n";
            return;
        }
        printStored();
        int idx = getChoice("Choose index: ", 1, encryptedMessages.size());
        if (idx == -1) return;
        std::string dec = swapNibbles(encryptedMessages[idx - 1]);
        std::cout << "Decrypted: " << dec << "\n";
    }
}

static void cbcHandler(int level) {
    int action = getChoice("1 � encrypt, 2 � decrypt, 0 � back: ", 0, 2);
    if (action == 0) return;
    if (action == 1) {
        std::string text = getInput("Enter text: ");
        char iv;
        if (level == 2) {
            iv = 'I';
        }
        else {
            std::string ivStr = getInput("Enter IV (one character): ");
            iv = ivStr.empty() ? 'I' : ivStr[0];
        }
        std::string enc = cbcEncrypt(text, iv);
        encryptedMessages.push_back(enc);
        std::cout << "Encrypted: ";
        printHex(enc);
        std::cout << " (index " << encryptedMessages.size() << ")\n";
    }
    else {
        if (encryptedMessages.empty()) {
            std::cout << "No saved messages.\n";
            return;
        }
        printStored();
        int idx = getChoice("Choose index: ", 1, encryptedMessages.size());
        if (idx == -1) return;
        char iv;
        if (level == 2) {
            iv = 'I';
        }
        else {
            std::string ivStr = getInput("Enter IV (one character): ");
            iv = ivStr.empty() ? 'I' : ivStr[0];
        }
        std::string dec = cbcDecrypt(encryptedMessages[idx - 1], iv);
        std::cout << "Decrypted: " << dec << "\n";
    }
}

void runLevel(int level) {
    std::cout << "\n=== Sandbox (level " << level << ") ===\n";
    while (true) {
        std::cout << "\nChoose cipher:\n";
        std::cout << "1)Caesar\n2)Atbash\n3)XOR\n4)Nibble Swap\n5)Simple CBC\n0) Back to main menu\n";
        std::cout << "Your choice:\n";
        std::string choiceStr;
        std::cin >> choiceStr;
        if (choiceStr == "exit") return;
        if (!IsNumber(choiceStr)) {
            std::cerr << "Not correct input!" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(1500));
            continue;
        }

        if (std::stoi(choiceStr) == 0) return;

        switch (std::stoi(choiceStr)) {
        case 1:
            caesarHandler(level);
            break;
        case 2:
            atbashHandler(level);
            break;
        case 3:
            xorHandler(level);
            break;
        case 4:
            swapHandler(level);
            break;
        case 5:
            cbcHandler(level);
            break;
        default:
            std::cerr << "Not correct input!" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(1500));
            break;
        }
    }
}
