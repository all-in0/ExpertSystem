//
// Created by all-i on 24.02.2019.
//

#ifndef EXPERTSYSTEM_EXPERTSYSTEM_H
#define EXPERTSYSTEM_EXPERTSYSTEM_H

#include "CommanParser.hpp"


class ExpertSystem {
public:
    explicit ExpertSystem(std::string file);
    //bool ManageAnd(std::string first, std::string second);
    bool solve();
    bool findState(char l);
    bool solveRule(std::pair<std::string, std::string> rule, char l);
    letterType manageType(char letter, std::string recursion, std::string str);
private:
    CommandParser parser;
    std::vector<std::pair<std::string, std::string>> mRecursionMap;
};


#endif //EXPERTSYSTEM_EXPERTSYSTEM_H
