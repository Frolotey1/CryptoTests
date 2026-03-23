#include "TaskGenerator.h"
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

Task generateCaesarTask(int level) {
Task task;
task.cipher_type = "caesar";
task.level = level;
std::string original = randomWord();
int shift = 0;
if (level == 1) shift = rand() % 25 + 1;
else if (level == 2) shift = 3;
else shift = rand() % 25 + 1; // для уровня 3
task.shift = shift;
std::string encrypted = caesarEncrypt(original, shift);
task.question = "Decrypt: " + encrypted;
task.answer = original;
return task;
}

Task generateAtbashTask(int level) {
Task task;
task.cipher_type = "atbash";
task.level = level;
std::string original = randomWord();
std::string encrypted = atbash(original);
task.question = "Decrypt: " + encrypted;
task.answer = original;
return task;
}

Task generateXorTask(int level) {
Task task;
task.cipher_type = "xor";
task.level = level;
std::string original = randomWord();
char key = (level == 2) ? 'K' : (char)(rand() % 256);
task.xor_key = key;
std::string encrypted = xorEncrypt(original, key);
std::stringstream ss;
for (unsigned char c : encrypted) ss << std::hex << (int)c << " ";
task.question = "Decrypt (hex): " + ss.str();
task.answer = original;
return task;
}

Task generateSwapNibblesTask(int level) {
Task task;
task.cipher_type = "swap_nibbles";
task.level = level;
std::string original = randomWord();
std::string encrypted = swapNibbles(original);
std::stringstream ss;
for (unsigned char c : encrypted) ss << std::hex << (int)c << " ";
task.question = "Decrypt (hex): " + ss.str();
task.answer = original;
return task;
}

Task generateCbcTask(int level) {
Task task;
task.cipher_type = "cbc";
task.level = level;
std::string original = randomWord();
char iv = (level == 2) ? 'I' : (char)(rand() % 256);
std::string encrypted = cbcEncrypt(original, iv);
std::stringstream ss;
for (unsigned char c : encrypted) ss << std::hex << (int)c << " ";
task.question = "Decrypt (hex): " + ss.str();
task.answer = original;
return task;
}
