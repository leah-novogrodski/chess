#pragma once

#include <vector>
#include <string>
#include <istream>
#include <unordered_set>
#include <memory>
#include <optional>

class BoardParser {
public:
    static std::unique_ptr<BoardParser> create(const std::unordered_set<std::string>& validTokens);

    explicit BoardParser(const std::unordered_set<std::string>& validTokens);

    std::vector<std::vector<std::string>> parse(std::istream& input) const;

private:
    std::unordered_set<std::string> m_validTokens;

    bool isValidToken(const std::string& token) const;
    std::vector<std::string> parseRow(const std::string& line) const;
};