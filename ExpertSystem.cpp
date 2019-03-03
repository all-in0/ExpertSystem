#include <utility>

//
// Created by all-i on 24.02.2019.
//

#include "ExpertSystem.h"

ExpertSystem::ExpertSystem(std::string file) :
    parser(std::move(file))
{

}

bool ExpertSystem::solve() {
    auto &query = parser.mQuery;
    for (auto & l : query) {
        findState(l);
        //std::cout << l.first << " is " << (l.second == letterType::iTrue ? "true" : "false") << std::endl;
    }
    return false;
}

letterType ExpertSystem::manageType(char letter, std::string recursion, std::string str) {

    return iFalse;
}

bool ExpertSystem::findState(char l) {

    for (auto & cond : parser.mConditions){
        if (cond.second.find(l) != std::string::npos){
            if(std::find_if(mRecursionMap.begin(), mRecursionMap.end(), cond) != mRecursionMap.end()) continue;
            mRecursionMap.emplace_back(cond);
            solveRule(cond, l);
        }
    }
    return false;
}

bool ExpertSystem::solveRule(std::pair<std::string, std::string> rule, char l) {
    
    return false;
}
