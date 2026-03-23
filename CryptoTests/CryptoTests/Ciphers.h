#ifndef CIPHERS_H
#define CIPHERS_H
#include "Header.h"

std::string caesarEncrypt(const std::string& text, int shift);
std::string caesarDecrypt(const std::string& cipher, int shift);
std::string atbash(const std::string& text);
std::string xorEncrypt(const std::string& text, char key);
std::string xorDecrypt(const std::string& cipher, char key);
std::string swapNibbles(const std::string& text);
std::string cbcEncrypt(const std::string& text, char iv);
std::string cbcDecrypt(const std::string& cipher, char iv);

#endif