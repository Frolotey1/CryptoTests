#ifndef TASK_GENERATOR_H
#define  TASK_GENERATOR_H
#include "Header.h"

struct Task {
std::string question = "";
std::string answer = "";
std::string cipher_type = "";
int level = 0;
int shift = 0; // для Цезаря
char xor_key = ' ';
explicit Task() = default;  // для XOR
};

Task generateCaesarTask(int level);
Task generateAtbashTask(int level);
Task generateXorTask(int level);
Task generateSwapNibblesTask(int level);
Task generateCbcTask(int level);

#endif // TASK_GENERATOR_H
