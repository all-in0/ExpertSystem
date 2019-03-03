//
// Created by all-in0 on 26.01.19.
//

#include "CommanParser.hpp"



CommandParser::CommandParser(std::string file) :
    pattern("<=>^|=!()")
{
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

bool CommandParser::Conditions(std::string &line) {
    for(int itr = 0; itr < line.length() ;itr++) {
        if (isspace(line[itr]) || pattern.find(line[itr]) != std::string::npos)
            continue;
        if (!isupper(line[itr]))
            return false;
        mLetters.insert(std::pair<char, letterType >(line[itr], letterType::iUnknown));
    }
  //  if (std::count(line.begin(), line.end(), "=>") != 1)
  //      return false;
    size_t pos = line.find("=>");
    if (pos < 0  || line.length() == pos + 2 )
        return false;
    mConditions.insert(std::pair<std::string, std::string>(line.substr(0, pos), line.substr(pos + 2)));
    return true;
}
