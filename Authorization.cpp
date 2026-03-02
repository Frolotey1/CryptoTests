#include "Authorization.h"
#include "CryptoTestEasy.h"

std::vector<User> users = { {"user", "user", "Client"} };
std::string currentUserStatus;

bool CheckLogin(const std::string& str)
{
    // Check length
    if (str.size() < 5 || str.size() > 20) {
        std::cout << "Invalid login length. Must be between 5 and 20 characters.\n";
        Sleep(1500);
        return false;
    }

    // Allowed characters (only letters)
    for (char c : str) {
        if (!isalpha(c)) {
            std::cout << "Invalid characters in login. Only letters A-Z, a-z are allowed.\n";
            Sleep(1500);
            return false;
        }
    }

    // Uniqueness
    for (const auto& user : users) {
        if (user.login == str) {
            std::cout << "User with this login already exists!\n";
            Sleep(1500);
            return false;
        }
    }
    return true;
}

// Check password
bool CheckPass(const std::string& str) {
    if (str.size() < 5 || str.size() > 64) {
        std::cout << "Invalid password length! Must be between 5 and 64 characters.\n";
        Sleep(1500);
        return false;
    }

    // ASCII printable characters
    std::unordered_set<char> allowed;
    for (char c = '!'; c <= '~'; ++c) {
        allowed.insert(c);
    }

    for (char c : str) {
        if (allowed.find(c) == allowed.end()) {
            std::cout << "Invalid characters in password. Only printable ASCII characters allowed.\n";
            Sleep(1500);
            return false;
        }
    }

    // Special characters
    std::unordered_set<char> special = {
        '!', '@', '#', '%', '^', '&', '*', '(', ')', '-', '_', '=', '+',
        '/', '?', '|', '\\', '\"', '\'', ',', '.', '>', '<', '~', '`', ':',
        ';', '{', '}', '[', ']'
    };

    int specialCount = 0;
    for (char c : str) {
        if (special.count(c)) {
            specialCount++;
            if (specialCount >= 3) break;
        }
    }

    if (specialCount < 3) {
        std::cout << "At least 3 special characters are required.\n";
        Sleep(1500);
        return false;
    }

    return true;
}

bool Login() {
    std::string choose;
    std::string login, pass;
    while (true)
    {
        std::cout << "\n=== CRYPTOGRAPHIC TRAINER ===\n";
        std::cout << "\n=== Login ===\n";
        std::cout << "1 � Login\n";
        std::cout << "2 � Register\n";
        std::cout << "0 � Exit\n";
        std::cout << "Your choice: ";
        Getline(choose);

        if (choose == "0") {
            return false;
        }
        else if (choose == "1") {
            while (true) {
                std::cout << "Enter login or \"exit\" to return to menu: ";
                Getline(login);
                if (login == "exit") break;

                std::cout << "Enter password: ";
                Getline(pass);

                // Search in vector
                bool found = false;
                for (const auto& user : users) {
                    if (user.login == login && user.password == pass) {
                        currentUserStatus = user.status;
                        std::cout << "\nWelcome, " << login << "!\n";
                        std::cout << "Your status: " << currentUserStatus << "\n";
                        system("pause");
                        return true;
                    }
                }

                if (!found) {
                    std::cout << "Invalid login or password!\n";
                    Err(1500);
                }
            }
        }
        else if (choose == "2") {
            // Registration
            RegisterUser();
        }
        else {
            Err(); // invalid input
        }
    }
}

void RegisterUser()
{
    std::string login, pass;

    // Enter login
    while (true) {
        system("cls");
        std::cout << "\t=== Register New User ===\n";
        std::cout << "Enter login (5-20 characters, only letters) or \"exit\": \n";
        Getline(login);
        if (login == "exit" || login == "Exit") {
            std::cout << "Registration cancelled.\n";
            Sleep(1500);
            return;
        }
        if (CheckLogin(login)) break;
    }

    // Enter password
    while (true) {
        system("cls");
        std::cout << "\n=== CRYPTOGRAPHIC TRAINER ===\n";
        std::cout << "\t=== Registration ===\n";
        std::cout << "Enter password (5-64 characters, at least 3 special characters) or \"exit\": \n";
        Getline(pass);
        if (pass == "exit" || pass == "Exit") {
            std::cout << "Registration cancelled.\n";
            Sleep(1500);
            return;
        }
        if (CheckPass(pass)) break;
    }

    users.push_back({ login, pass, "Client" });

    std::cout << "\nUser successfully registered!\n";
    system("pause");
}
