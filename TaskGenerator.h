#ifndef TASK_GENERATOR_H
#define  TASK_GENERATOR_H

#include <string>
#include <vector>

struct Task {
std::string question;
std::string answer;
std::string cipher_type;
int level;
int shift; // для Цезаря
char xor_key; // для XOR
};

Task generateCaesarTask(int level);
Task generateAtbashTask(int level);
Task generateXorTask(int level);
Task generateSwapNibblesTask(int level);
Task generateCbcTask(int level);

#endif // TASK_GENERATOR_H
