#include "Database.hpp"
#include "UserRepository.hpp"

#include <iostream>

int main() {
    try {
        Database db("chess_users.db");

        const std::string username = "Leah";
        const std::string correctPassword = "14789632";
        const std::string email = "Leah@example.com";
        const std::string wrongPassword = "wrongpass";

        RegisterResult reg = registerUser(db, username,email, correctPassword);
        if (reg.success) {
            std::cout << "Registered user '" << username << "'." << std::endl;
        } else if (reg.reason == "email_taken") {
            std::cout << "User '" << username << "' already exists (skipping registration)." << std::endl;
        } else {
            std::cout << "FAIL: registration error: " << reg.reason << std::endl;
        }

        LoginResult correctLogin = loginUser(db, email, correctPassword);
        if (correctLogin.success) {
            std::cout << "PASS: login with correct password succeeded, rating=" << correctLogin.rating << std::endl;
        } else {
            std::cout << "FAIL: login with correct password failed, reason=" << correctLogin.reason << std::endl;
        }

        LoginResult wrongLogin = loginUser(db, username, wrongPassword);
        if (!wrongLogin.success && wrongLogin.reason == "wrong_password") {
            std::cout << "PASS: login with wrong password correctly rejected (reason=wrong_password)." << std::endl;
        } else if (wrongLogin.success) {
            std::cout << "FAIL: login with wrong password unexpectedly succeeded!" << std::endl;
        } else {
            std::cout << "FAIL: login with wrong password rejected for unexpected reason: " << wrongLogin.reason << std::endl;
        }

        return 0;
    } catch (const std::exception& e) {
        std::cerr << "persistence_demo error: " << e.what() << std::endl;
        return 1;
    }
}