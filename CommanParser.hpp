//
// Created by all-in0 on 26.01.19.
//

#ifndef EXPERTSYSTEM_COMMANPARSER_HPP
#define EXPERTSYSTEM_COMMANPARSER_HPP

#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <regex>

class CommandParser {
public:
    explicit CommandParser(std::string file);
    ~CommandParser();

private:
    bool ParseLine(std::string & line);
    bool ParseFact(std::string & line);
    bool ParseAnswer(std::string & line);
    bool Conditions(std::string & line);
    std::vector<std::string> AllLines;
};


#endif //EXPERTSYSTEM_COMMANPARSER_HPP
