#include "Ciphers.h"

std::string caesarEncrypt(const std::string& text, int shift) {
    std::string result;
    for (char c : text) {
        if (isalpha(c)) {
            char base = islower(c) ? 'a' : 'A'; 
            result += (c - base + shift) % 26 + base;
        }
        else {
            result += c; 
        }
    }
    return result;
}

std::string caesarDecrypt(const std::string& cipher, int shift) {
    return caesarEncrypt(cipher, 26 - shift); 
}

std::string atbash(const std::string& text) {
    std::string result;
    for (char c : text) {
        if (isalpha(c)) {
            char base = islower(c) ? 'a' : 'A'; 
            result += base + (25 - (c - base));
        }
        else {
            result += c; 
        }
    }
    return result;
}

std::string xorEncrypt(const std::string& text, char key) {
    std::string result = text;
    for (char& c : result) c ^= key;
    return result;
}

std::string xorDecrypt(const std::string& cipher, char key) {
    return xorEncrypt(cipher, key);
}

std::string swapNibbles(const std::string& text) {
    std::string result;
    for (unsigned char c : text) {
        unsigned char swapped = ((c & 0x0F) << 4) | ((c & 0xF0) >> 4);
        result += static_cast<char>(swapped);
    }
    return result;
}

std::string cbcEncrypt(const std::string& text, char iv) {
    std::string result;
    char prev = iv;
    for (char c : text) {
        char encrypted = c ^ prev;
        result += encrypted;
        prev = encrypted;
    }
    return result;
}

std::string cbcDecrypt(const std::string& cipher, char iv) {
    std::string result;
    char prev = iv;
    for (char c : cipher) {
        char decrypted = c ^ prev;
        result += decrypted;
        prev = c;
    }
    return result;
}
