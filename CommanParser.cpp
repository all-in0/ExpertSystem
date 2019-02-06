//
// Created by all-in0 on 26.01.19.
//

#include "CommanParser.hpp"

CommandParser::CommandParser(std::string file) {
    std::istringstream stream(file);
    std::string line;
    while (std::getline(stream, line))
        ParseLine(line);
}

CommandParser::~CommandParser() {

}

bool CommandParser::ParseLine(std::string & line) {
    line.erase(std::remove_if(line.begin(), line.end(), isspace),line.end());
    if (line.find('#') != std::string::npos)
        line.erase(line.find('#')); //check if # at the middle of string
    if (line.length() < 2)
        return true;
    AllLines.push_back(line);
    if (line[0] == '?')
        return ParseFact(line);
    else if (line[0] == '=')
        return ParseAnswer(line);
    return Conditions(line);
}

bool CommandParser::ParseFact(std::string &line) {
    return false;
}

bool CommandParser::ParseAnswer(std::string &line) {
    return false;
}

bool CommandParser::Conditions(std::string &line) {
    return false;
}
