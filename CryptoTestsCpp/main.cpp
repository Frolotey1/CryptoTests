#include "nlohmann/json.hpp"
#include "RunApplication.h"
#include "TaskGenerator.h"

using json = nlohmann::json;

int main(int argc, char* argv[]) {
    // Парсинг аргументов
    std::string mode = "generate";
    std::string cipher = "caesar";
    int level = 1;
    std::string text;
    int shift = 0;
    char key = 0;
    char iv = 0;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--mode" && i+1 < argc) mode = argv[++i];
        else if (arg == "--cipher" && i+1 < argc) cipher = argv[++i];
        else if (arg == "--level" && i+1 < argc) level = std::stoi(argv[++i]);
        else if (arg == "--text" && i+1 < argc) text = argv[++i];
        else if (arg == "--shift" && i+1 < argc) shift = std::stoi(argv[++i]);
        else if (arg == "--key" && i+1 < argc) key = argv[++i][0];
        else if (arg == "--iv" && i+1 < argc) iv = argv[++i][0];
    }

    json output;

    if (mode == "generate") {
        Task task;
        if (cipher == "caesar") task = generateCaesarTask(level);
        else if (cipher == "atbash") task = generateAtbashTask(level);
        else if (cipher == "xor") task = generateXorTask(level);
        else if (cipher == "swap_nibbles") task = generateSwapNibblesTask(level);
        else if (cipher == "cbc") task = generateCbcTask(level);
        else {
            output["error"] = "Unknown cipher";
            std::cout << output.dump() << std::endl;
            return 1;
        }
        output["question"] = task.question;
        output["answer"] = task.answer;
        output["cipher_type"] = task.cipher_type;
        output["level"] = task.level;
        if (cipher == "caesar") output["shift"] = task.shift;
        if (cipher == "xor") output["key"] = (int)task.xor_key;
    }
    else if (mode == "check") {
        output["result"] = true;
    }
    else {
        output["error"] = "Unknown mode";
    }

    std::cout << output.dump() << std::endl;
    return 0;
}
