//
// Created by all-i on 24.02.2019.
//

#ifndef EXPERTSYSTEM_EXPERTSYSTEM_H
#define EXPERTSYSTEM_EXPERTSYSTEM_H

#include "CommanParser.hpp"
#include <cmath>


class ExpertSystem {
public:
    explicit ExpertSystem(std::string file);
    //bool ManageAnd(std::string first, std::string second);
    bool solve();
    bool findState(char l);
    bool solveRule(std::pair<std::string, std::string> rule, char l);
    letterType manageType(char letter, std::string recursion, std::string str);
    bool checkFact(char l);
    letterType  checkRight(std::string right);
    letterType checkLeft(std::string left);
    std::string::iterator rightStr(std::string::iterator it, letterType & currentState, char command);
    std::string::iterator leftStr(std::string::iterator it, letterType & currentState, char command);
    void fixState(char fact, letterType newState);
    std::map<char, letterType> solutionsToFacts(std::string rhs, std::map<std::string, letterType> solutions);
    letterType getState(char fact);
    std::map<std::string, letterType> generateSolution(std::string right);
private:
    CommandParser parser;
    std::vector<std::pair<std::string, std::string>> mRecursionMap;
};


#endif //EXPERTSYSTEM_EXPERTSYSTEM_H
