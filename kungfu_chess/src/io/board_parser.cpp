#include "io/board_parser.hpp"
#include <sstream>
#include <stdexcept>

std::unique_ptr<BoardParser> BoardParser::create(const std::unordered_set<std::string>& validTokens) {
    return std::make_unique<BoardParser>(validTokens);
}

BoardParser::BoardParser(const std::unordered_set<std::string>& validTokens)
    : m_validTokens(validTokens) {
}

bool BoardParser::isValidToken(const std::string& token) const {
    return m_validTokens.find(token) != m_validTokens.end();
}

std::vector<std::string> BoardParser::parseRow(const std::string& line) const {
    std::vector<std::string> rowTokens;
    std::stringstream stream(line);
    std::string token;

    while (stream >> token) {
        if (!isValidToken(token)) {
            throw std::invalid_argument("Invalid token detected: " + token);
        }
        rowTokens.push_back(token);
    }

    return rowTokens;
}

std::vector<std::vector<std::string>> BoardParser::parse(std::istream& input) const {
    std::vector<std::vector<std::string>> parsedBoard;
    std::string line;
    bool isBoardSection = false;
    std::optional<size_t> boardWidth = std::nullopt;

    while (std::getline(input, line)) {
        if (line == "Board:") {
            isBoardSection = true;
            continue;
        }

        if (line == "Commands:") {
            break;
        }

        if (isBoardSection) {
            if (line.empty()) {
                continue;
            }

            std::vector<std::string> rowTokens = parseRow(line);
            
            if (rowTokens.empty()) {
                continue;
            }

            if (!boardWidth.has_value()) {
                boardWidth = rowTokens.size();
            } else if (boardWidth.value() != rowTokens.size()) {
                throw std::length_error("Row width mismatch detected");
            }

            parsedBoard.push_back(rowTokens);
        }
    }

    if (parsedBoard.empty()) {
        throw std::runtime_error("Empty board structure provided");
    }

    return parsedBoard;
}