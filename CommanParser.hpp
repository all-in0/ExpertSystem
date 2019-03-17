//
// Created by all-in0 on 26.01.19.
//

#ifndef EXPERTSYSTEM_COMMANPARSER_HPP
#define EXPERTSYSTEM_COMMANPARSER_HPP

#include <string>
#include <iostream>
#include <fstream>
#include <list>
#include <algorithm>
#include <sstream>
#include <vector>
#include <regex>

enum letterType{
    iUnknown = 0,
    iTrue,
    iFalse,
    iError
};


class CommandParser {
public:
    explicit CommandParser(std::string file);
    ~CommandParser();

public:
    bool ParseLine(std::string & line);
    bool ParseQuery(std::string & line);
    bool ParseFact(std::string & line);
    bool Conditions(std::string & line);
    std::string simplifyCondition(std::string  line);

    std::string pattern;
    std::vector<std::string> AllLines;
    std::vector<std::string> mCommands;
    std::vector<std::pair<std::string, std::string>> mTmpCnd;
    char mCondReplace;
    std::map<char, letterType> mLetters;
    std::multimap<std::string, std::string> mConditions;
    std::list<char> mFacts;
    std::list<char> mQuery;
};


#endif //EXPERTSYSTEM_COMMANPARSER_HPP
