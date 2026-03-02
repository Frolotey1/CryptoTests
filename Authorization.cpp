
#include "Authorization.h"
#include "CryptoTestEasy.h"


std::vector<User> users = { {"user", "user", "Êëèåíò"} };
std::string currentUserStatus;

bool CheckLogin(const std::string& str)
{
    if (str.size() < 5 || str.size() > 20) {
        std::cout << "Ошибка ввода логина\n";
        return false;
    }
    
    for (char c : str) {
        if (!isalpha(c)) {
            std::cout << "Íåêîððåêòíûå ñèìâîëû â ëîãèíå. Ðàçðåøåíû òîëüêî áóêâû A-Z, a-z\n";
            return false;
        }
    }

    for (const auto& user : users) {
        if (user.login == str) {
         
            std::cout << "Ïîëüçîâàòåëü ñ òàêèì ëîãèíîì óæå ñóùåñòâóåò!\n";
            return false;
        }
    }
    return true;
}

bool CheckPass(const std::string& str) {
    if (str.size() < 5 || str.size() > 64) {
        std::cout << "Ошибка ввода пароля\n";
        return false;
    }

    std::unordered_set<char> allowed;
    for (char c = '!'; c <= '~'; ++c) {
        allowed.insert(c);
    }

    for (char c : str) {
        if (allowed.find(c) == allowed.end()) {
            std::cout << "Íåêîððåêòíûå ñèìâîëû â ïàðîëå. Ðàçðåøåíû òîëüêî ïå÷àòíûå ASCII ñèìâîëû.\n";
            return false;
        }
    }

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
        std::cout << "Òðåáóåòñÿ ìèíèìóì 3 ñïåöèàëüíûõ ñèìâîëà\n";
        return false;
    }

    return true;
}

bool Login() {
    std::string choose;
    std::string login, pass;
    while (true)
    {
        std::cout << "\n=== ÊÐÈÏÒÎÃÐÀÔÈ×ÅÑÊÈÉ ÒÐÅÍÀÆ¨Ð ===\n";
        std::cout << "\n=== Âõîä â ñèñòåìó ===\n";
        std::cout << "1 – Âõîä\n";
        std::cout << "2 – Ðåãèñòðàöèÿ\n";
        std::cout << "0 – Âûõîä\n";
        std::cout << "Âàø âûáîð: ";
        Getline(choose);

        if (choose == "0") {
            return false;
        }
        else if (choose == "1") {
            
            
            while (true) {
                std::cout << "Ââåäèòå ëîãèí èëè \"exit\" äëÿ âîçâðàòà â ìåíþ: ";
                Getline(login);
                if (login == "exit") break; 

                std::cout << "Ââåäèòå ïàðîëü: ";
                Getline(pass);

                bool found = false;
                for (const auto& user : users) {
                    if (user.login == login && user.password == pass) {
                        currentUserStatus = user.status;
                        std::cout << "\nÄîáðî ïîæàëîâàòü, " << login << "\n";
                        std::cout << "Âàø ñòàòóñ: " << currentUserStatus << "\n";
                        system("pause");
                        return true;
                    }
                }

                if (!found) {
                    std::cout << "Íåâåðíûé ëîãèí èëè ïàðîëü!\n";
                    Err(1500);
                }
            }
        }
        else if (choose == "2") {
            RegisterUser();
      
        }
        else {
            Err(); 
        }
    }
}

void RegisterUser()
{
    std::string login, pass;

    while (true) {
        system("cls");
        std::cout << "\t=== Ðåãèñòðàöèÿ íîâîãî ïîëüçîâàòåëÿ ===\n";
        std::cout << "Ââåäèòå ëîãèí (îò 5 äî 20 ñèìâîëîâ, òîëüêî áóêâû) èëè \"exit\": \n";
        Getline(login);
        if (login == "exit" || login == "Exit") {
            std::cout << "Ðåãèñòðàöèÿ îòìåíåíà.\n";
            return;
        }
        if (CheckLogin(login)) break;
    }
    
    while (true) {
        system("cls");
        std::cout << "\n=== ÊÐÈÏÒÎÃÐÀÔÈ×ÅÑÊÈÉ ÒÐÅÍÀÆ¨Ð ===\n";
        std::cout << "\t=== Ðåãèñòðàöèÿ ===\n";
        std::cout << "Ââåäèòå ïàðîëü (îò 5 äî 64 ñèìâîëîâ, ìèíèìóì 3 ñïåöñèìâîëà) èëè \"exit\": \n";
      
        Getline(pass);
        if (pass == "exit" || pass == "Exit") {
            std::cout << "Ðåãèñòðàöèÿ îòìåíåíà.\n";
            return;
        }
        if (CheckPass(pass)) break;
    }

    users.push_back({ login, pass, "Êëèåíò" });

    std::cout << "\nÏîëüçîâàòåëü óñïåøíî çàðåãèñòðèðîâàí\n";
   
    system("pause");
}
