//
// Created by all-in0 on 26.01.19.
//

#include "CommanParser.hpp"



CommandParser::CommandParser(std::string file) :
    pattern("<=>^|=!+()"),
    mCondReplace('a')
{
    std::istringstream stream(file);
    std::string line;
    size_t letters;
    while (std::getline(stream, line))
        ParseLine(line);
    for (std::pair<std::string, std::string> ln : mConditions){
        letters = 0;
        for(auto a : ln.first)
            if (isalpha(a) || a == '(' || a == ')')
                letters++;
        if (letters > 2)
            ln.first = simplifyCondition(ln.first);
        letters = 0;
        for(auto a : ln.second )
            if (isalpha(a) || a == '(' || a == ')')
                letters++;
        if (letters > 2)
            ln.second = simplifyCondition(ln.second);
        mTmpCnd.push_back(ln);
    }
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
        return ParseQuery(line);
    else if (line[0] == '=')
        return ParseFact(line);
    return Conditions(line);
}

bool CommandParser::ParseQuery(std::string &line) {
    for(int itr = 1; itr < line.length() ;itr++){
        if (isspace(line[itr]))
            continue;
        if (!isupper(line[itr])){
            return false;
        }
        if (std::find(mQuery.begin(), mQuery.end(), line[itr]) != mQuery.end())
            return false;
        mQuery.push_back(line[itr]);
    }
    return true;
}

bool CommandParser::ParseFact(std::string &line) {
    for(int itr = 1; itr < line.length() ;itr++){
        if (isspace(line[itr]))
            continue;
        if (!isupper(line[itr])){
            return false;
        }
        if (std::find(mFacts.begin(), mFacts.end(), line[itr]) != mFacts.end())
            return false;
        mFacts.push_back(line[itr]);
        if (mLetters.find(line[itr]) == mLetters.end())
            return false;
        mLetters[line[itr]] = letterType::iTrue;
    }
    return true;
}


std::string CommandParser::simplifyCondition(std::string  line){
    size_t letters = 0;
    size_t brack = 0;
    size_t brTmp = 0;
    bool br = false;
    for (size_t itr = 0; itr < line.length(); itr++){
        if (line[itr] == '('){
            if (brack == 0) brTmp = itr;
            brack++;
            br = true;
        }
        else if (line[itr] == ')'){
            brack--;
        }
        if (br && brack == 0) {
            line.replace(brTmp, itr-brTmp + 1, simplifyCondition(line.substr(brTmp + 1, itr - brTmp - 1)));
            br = false;
        }
    }
    for(auto a : line)
        if (isalpha(a))
            letters++;
    if (letters == 1)
        return line; //check!!
    if (letters > 2)
        line.replace(2, std::string::npos, simplifyCondition(line.substr(2)));
    std::string NewValue(1, mCondReplace++);
    mTmpCnd.emplace_back(std::pair<std::string, std::string>(line, NewValue));
    std::cout << NewValue << std::endl;
    return NewValue;
}

bool CommandParser::Conditions(std::string &line) {
    for (char &itr : line) {
        if (isspace(itr) || pattern.find(itr) != std::string::npos)
            continue;
        if (!isupper(itr))
            return false;
        mLetters.insert(std::pair<char, letterType >(itr, letterType::iUnknown));
    }
    if (std::count(line.begin(), line.end(), '=') != 1 || std::count(line.begin(), line.end(), '>') != 1)
        return false;
    auto pos = line.find("=>");
    if (pos == std::string::npos || pos < 0  || line.length() == pos + 2 )
        return false;
    mConditions.insert(std::pair<std::string, std::string>(line.substr(0, pos), line.substr(pos + 2)));
    return true;
}
