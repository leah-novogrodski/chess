// src/main.cpp
#include "../include/core/Board.hpp"
#include <iostream>

int main() {
    try {
        // קריאה ווידוא מתוך קלט המערכת הסטנדרטי
        std::vector<std::vector<std::string>> board = core::Board::parse(std::cin);
        // הדפסה חזרה ללא שום טקסט נוסף
        core::Board::print(board, std::cout);
        
    } catch (const std::exception& e) {
        // ה-VPL מצפה שלא נדפיס טקסטים של שגיאות מותאמות, לכן נחזיר קוד שגיאה
        return 1;
    }

    return 0;
}