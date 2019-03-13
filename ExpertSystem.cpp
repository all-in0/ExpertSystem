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
    auto &letter = parser.mLetters;
    for (auto & l : letter) {
        findState(l.first);
        mRecursionMap.clear();
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
        //    if(std::find_if(mRecursionMap.begin(), mRecursionMap.end(), cond) != mRecursionMap.end()) continue;
            mRecursionMap.emplace_back(cond);
            solveRule(cond, l);
        }
    }
    return false;
}


letterType					ExpertSystem::getState(char fact) {
    for (auto f : parser.mLetters) {
        if (fact == f.first)
            return f.second;
    }
    return iUnknown;
}


std::string::iterator 		ExpertSystem::rightStr(std::string::iterator it, letterType & currentState, char command) {
    char 					nextFact;
    letterType 					nextState;
    bool					bang = false;

    it++;
    nextFact = *it;

    while (nextFact == '!') {
        it++;
        nextFact = *it;
        bang = !bang;
    }

    nextState = (*it == '0') ? iFalse : iTrue;

    if (bang)
        nextState = (nextState == iTrue) ? iFalse : iTrue;

    switch (command) {
        case '+' :
            currentState = (currentState == iTrue && nextState == iTrue) ? iTrue : iFalse;
            break ;
        case '|' :
            currentState = (currentState == iTrue || nextState == iTrue) ? iTrue : iFalse;
            break ;
        case '^' :
            currentState = (currentState == iTrue ^ nextState == iTrue) ? iTrue : iFalse;
            break ;
        default:break;
    }

    return it;
}


std::string::iterator   ExpertSystem::leftStr(std::string::iterator it, letterType & currentState, char command) {
  // need refactor

    char    nextFact;
    letterType  nextState;
    bool    bang = false;

    it++;
    nextFact = *it;

    while (nextFact == '!') {
        it++;
        nextFact = *it;
        bang = !bang;
    }

    nextState = getState(*it);

    if (bang)
        nextState = (nextState == iTrue) ? iFalse : iTrue;

    switch (command) {
        case '+' :
            currentState = (currentState == iTrue && nextState == iTrue) ? iTrue : iFalse;
            break ;
        case '|' :
            currentState = (currentState == iTrue || nextState == iTrue) ? iTrue : iFalse;
            break ;
        case '^' :
            currentState = (currentState == iTrue ^ nextState == iTrue) ? iTrue : iFalse;
            break ;
        default:break;
    }

    return it;
}


letterType  ExpertSystem::checkRight(std::string right) {
    right.insert(0, "+");

    letterType					currentState = iTrue;

    for(auto it = right.begin(); it != right.end(); ++it) {
        switch (*it) {
            case '+' :
                it = leftStr(it, currentState, '+');
                break ;
            case '|' :
                it = leftStr(it, currentState, '|');
                break ;
            case '^' :
                it = leftStr(it, currentState, '^');
                break ;
            default:break;
        }
    }

    return currentState;
}


letterType  ExpertSystem::checkLeft(std::string left) {
    left.insert(0, "+");
    letterType  tmpState = letterType::iTrue;

    for (auto it = left.begin(); it != left.end(); it++) {
        switch (*it) {
            case '+' :
                it = leftStr(it, tmpState, '+');
                break ;
            case '|' :
                it = leftStr(it, tmpState, '|');
                break ;
            case '^' :
                it = leftStr(it, tmpState, '^');
                break ;
            default : break;
        }
    }

    return tmpState;
}


std::map<char, letterType> ExpertSystem::solutionsToFacts(std::string rhs, std::map<std::string, letterType> solutions) {
    std::map<char, letterType> 					facts;
    auto		site = solutions.end();

    for (size_t i = 0; i < rhs.size(); i++) {
        if (checkFact(rhs[i])) {
            std::list<char> 	tmpCharList;

            for (auto	sit  = solutions.begin(); sit != site; sit++) {
                tmpCharList.push_back((sit->first)[i]);
            }

            tmpCharList.unique();

            if (tmpCharList.size() >= 2)
                facts[rhs[i]] = iUnknown;//check if error
            else if (tmpCharList.front() == '0')
                facts[rhs[i]] = iFalse;
            else
                facts[rhs[i]] = iTrue;
        }
    }

    return facts;
}


std::map<std::string, letterType> ExpertSystem::generateSolution(std::string right) {
    std::map<std::string, letterType>   solutions;
    int n = 0;

    for (char c : right) {
        if (checkFact(c))
            n++;
    }

    int 						m, p, q;
    std::ostringstream 			oss;
    std::string 				tmpString;

    for (m = 0; m < pow(2, n); m++) {
        q = m;
        tmpString = right;
        for (p = n - 1; p >= 0; p--) {
            oss << int(q / pow(2, p));
            q = fmod(q, pow(2, p));

            for (size_t i = 0; i < tmpString.size(); i++) {
                if (checkFact(tmpString[i])) {
                    tmpString[i] = oss.str()[0];
                    break ;
                }
            }

            oss.str("");
        }
        solutions[tmpString] = iError; // unresolved
    }

    return solutions;
}



void					ExpertSystem::fixState(char fact, letterType newState) {
    std::map<char, letterType> & facts = parser.mLetters;
    letterType				oldState = facts[fact];

    switch (oldState) {
        case iFalse :
            switch (newState) {
                case iTrue :
                   // throw UpdateStateError(fact, oldState, newState);
                    break ;
                default :
                    break ;
            }
            break ;
        case iTrue :
            switch (newState) {
                case iFalse :
                    //throw UpdateStateError(fact, oldState, newState);
                    break ;
                default :
                    break ;
            }
            break ;
        case iUnknown : //undef
            switch (newState) {
                case iUnknown : //unsolved
                    break ;
                default :
                    facts[fact] = newState;
                    break ;
            }
            break ;
        case iError : //unsolved
            facts[fact] = newState;
            break ;
    }

   // setFacts(facts);

    return ;
}




bool ExpertSystem::solveRule(std::pair<std::string, std::string> rule, char l) {
    auto    left = rule.first;
    auto    right = rule.second;
    for(auto c : left)
        if (checkFact(c))
            findState(c);
    for(auto c : right)
        if (checkFact(c) && l != c)
            findState(c);
    letterType   lState  = checkLeft(left);
    if (lState == iTrue) {
        std::map<std::string, letterType> tmpSolutions = generateSolution(right);
        /*        for (auto	sit  = tmpSolutions.begin(); sit != tmpSolutions.end(); sit++)
            sit->second = checkRight(sit->first);*/
        for (auto &tmpSolution : tmpSolutions)
            tmpSolution.second = checkRight(tmpSolution.first); //check
        std::map<std::string, letterType> finalSolutions;

        for (auto &tmpSolution : tmpSolutions) {
            if (tmpSolution.second == iTrue)
                finalSolutions[tmpSolution.first] = tmpSolution.second;
        }
        std::map<char, letterType> 	    newFacts = solutionsToFacts(right, finalSolutions);


        for (auto fit  = newFacts.begin(); fit != newFacts.end(); fit++)
            fixState(fit->first, fit->second);
    }










    return false;
}

bool ExpertSystem::checkFact(char l) {
    for (auto & fact : parser.mFacts) {
        if (l == fact)
            return true;
    }
    return false ;
}
