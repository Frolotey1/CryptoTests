#include "Authorization.h"
#include "RunApplication.h"
#include "CryptoTestEasy.h"

std::vector<User> users{ {"user", "user", "Client"} };
std::string currentUserStatus;

bool CheckLogin(const std::string& str) {

    if (str.size() < 5 || str.size() > 20) {
        std::cerr << "Invalid login length. Must be between 5 and 20 characters.\n";
        return false;
    }

    std::for_each(str.begin(),str.end(),
                  [](auto& c){if(!std::isalpha(c,std::locale(""))){
                          std::cerr << "Invalid characters in login. Only letters A-Z, a-z are allowed.\n";
        }
        return false;
    });

    std::for_each(users.begin(),users.end(),
                  [str](auto& user){if(user.login == str){
                          std::cerr << "Error inputing of login for user!\n";
                          std::this_thread::sleep_for(std::chrono::milliseconds(1500));
        }
        return false;
    });
    return true;
}

bool CheckPass(const std::string& str) {

    if (str.size() < 5 || str.size() > 64) {
        std::cerr << "Invalid password length! Must be between 5 and 64 characters.\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(1500));
        return false;
    }

    std::unordered_set<char> allowed;
    for (char c = '!'; c <= '~'; ++c) {
        allowed.insert(c);
    }

    for(auto& c : allowed) {
        if(allowed.find(c) == allowed.end()) {
            std::cerr << "Invalid characters in password. Only printable ASCII characters allowed.\n";
            return false;
        }
    }

    std::unordered_set<char> special{
        '!', '@', '#', '%', '^', '&', '*', '(', ')', '-', '_', '=', '+',
        '/', '?', '|', '\\', '\"', '\'', ',', '.', '>', '<', '~', '`', ':',
        ';', '{', '}', '[', ']'
    };

    int specialCount = 0;

    for(auto& c : special) {
        if(special.count(c)){
            specialCount++;
            if (specialCount >= 3) break;
        }
    }

    if (specialCount < 3) {
        std::cerr << "At least 3 special characters are required.\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(1500));
        return false;
    }

    return true;
}

bool Login() {
    std::size_t choose = 0;
    std::string login = "", pass = "";
    while (true) {
        std::cout << "\n=== CRYPTOGRAPHIC TRAINER ===\n";
        std::cout << "\n=== Login ===\n";
        std::cout << "1)Login\n2)Register\n3)Delete Account\n4)Change Info\n5)Exit\nYour choice:\n";
        std::cin >> choose;

        if(choose == 1) {
            while (true) {
                std::cout << "Enter login or \"exit\" to return to menu:\n";
                std::cin >> login;
                if (login == "exit") break;

                std::cout << "Enter password:\n";
                std::cin >> pass;

                if(!captcha()) return false;

                for (const auto& user : users) {
                    if (user.login == login && user.password == pass) {
                        currentUserStatus = user.status;
                        std::cout << "\nWelcome, " << login << "!\n";
                        std::cout << "Your status: " << currentUserStatus << "\n";
                        return true;
                    }
                }

                std::cerr << "Invalid input!\n";
                return false;
            }
        }
        else if (choose == 2) {
            if(RegisterUser()) return true;
            else return false;
        }
        else if(choose == 3) {
            if(DeleteAccount()) return true;
            else return false;
        }
        else if(choose == 4) {
            if(Change_info()) return true;
            else return false;
        }
        else if(choose == 5)
            return false;
        else {
            std::cerr << "Invalid input!" << std::endl;
            return false;
        }
    }
    return true;
}

bool RegisterUser() {
    std::string login = "", pass = "", status = "Client";

    while (true) {
        std::cout << "\t=== Register New User ===\n";
        std::cout << "Enter login (5-20 characters, only letters) or \"exit\": \n";
        std::cin >> login;
        if (login == "exit") {
            std::cerr << "Registration cancelled!" << std::endl;
            return false;
        } 
        if(CheckLogin(login)) break;
    }

    while (true) {
        std::cout << "\n=== CRYPTOGRAPHIC TRAINER ===\n";
        std::cout << "\t=== Registration ===\n";
        std::cout << "Enter password (5-64 characters, at least 3 special characters) or \"exit\": \n";
        std::cin >> pass;
        if (pass == "exit") {
            std::cout << "Registration cancelled!" << std::endl;
            return false;
        }
        if (CheckPass(pass)) break;
    }

    User user;
    user.login = login;
    user.password = pass;
    user.status = status;

    users.emplace_back(user);

    std::cout << "\nUser successfully registered!\n" << std::endl;
    return true;
}

bool captcha() {
    std::size_t attempt = 0;
    std::vector rotate_words{"Bjarne","Stroustrup","is","the","creator","of","C++"};

    std::random_device device;
    std::mt19937 create_device(device());

    std::ostringstream os;

    std::string string = "", set_string = "", target_string = "";

    while(attempt < 3) {
        std::shuffle(rotate_words.begin(),rotate_words.end(),create_device);

        for(auto& push_str : rotate_words) {
            os << push_str << ' ';
        }

        target_string = os.str().substr(0,os.str().size() - 1);

        for(auto& get_every : rotate_words) {
            std::cout << get_every << " ";
        }
        std::cout << std::endl;

        std::cout << "Write the message from text:\n";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max());
        std::getline(std::cin,string);
        set_string = string;
        string.clear();

        if(set_string == target_string)
            return true;

        target_string = "";
        attempt++;
    }

    return false;
}

bool DeleteAccount() {
    std::string login = "", pass = "";

    std::cout << "Write your login:\n";
    std::cin >> login;
    std::cout << "Write your pass:\n";
    std::cin >> pass;

    std::string get_status = "";

    for(auto& check_login_pass : users) {
        if(check_login_pass.login == login && check_login_pass.password == pass) {
            get_status = check_login_pass.status;
        }
    }

    User delete_user;
    delete_user.login = login;
    delete_user.password = pass;
    delete_user.status = get_status;

    auto find_user = std::find(users.begin(),users.end(),delete_user);

    if(find_user == users.end()) {
        std::cerr << "Error input of login and password for user\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(1500));
        return false;
    }

    users.erase(find_user);
    std::cout << "\nUser was deleted successfully\n" << std::endl;
    return true;
}

bool Change_info() {
    std::string login = "", pass = "", status = "";

    std::cout << "Write the login for user:\n" << std::endl;
    std::cin >> login;
    std::cout << "Write the pass for user:\n";
    std::cin >> pass;
    std::cout << "Write the status for user:\n";
    std::cin >> status;

    auto find_user = std::find_if(users.begin(),users.end(),[&](const User& find){
        return find.login == login && find.password == pass;
    });

    if(find_user == users.end()) {
        std::cerr << "Error input of login and password for user" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1500));
        return false;
    } else {

        std::string new_login = "", new_pass = "", new_status = "";

        std::cout << "Write the new login for user:\n";
        std::cin >> new_login;
        if(!CheckLogin(new_login)) return false;
        std::cout << "Write the new pass for user:\n";
        std::cin >> new_pass;
        if(!CheckPass(new_pass)) return false;
        std::cout << "Write the new status for user:\n";
        std::cin >> new_status;

        auto find_from = std::find(users.begin(),users.end(),users.at(0));

        users.at(std::distance(find_from,find_user)).login = new_login;
        users.at(std::distance(find_from,find_user)).password = new_pass;
        users.at(std::distance(find_from,find_user)).status = new_status;
        return true;
    }
    return false;
}
