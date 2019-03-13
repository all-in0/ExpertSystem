
#include "CommanParser.hpp"
#include "ExpertSystem.h"

bool ReadFile(const std::string &filepath, std::string &content){
    std::ifstream stream(filepath);
    std::stringstream buffer;
    if (!stream.good())
        return false;
    buffer << stream.rdbuf();
    content = buffer.str();
    stream.close();
    return true;
}

int main(int ac, char **av) {
    if (ac != 2) {
        std::cout << "Usage: " << "./ExpertSystem" << " \"path to file\".\n";
        return 0;
    }
    std::string file;
    if (!ReadFile(av[1],file)) {
        std::cout << "Failed to open file!";
        return 0;
    }
   // std::cout << file  << std::endl; //debug
    ExpertSystem system(file);
    system.solve();
    int a;
    std::cin >> a ;
    //ExpertSystem solver(parser);
    return 0;
}