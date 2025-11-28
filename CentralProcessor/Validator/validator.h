#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <fstream>
#include <map>
#include <vector>
#include <string>
using std::vector;


class Validator {
private:
    vector <std::string> variables;
    std::ifstream source;
    std::ofstream repos;
    std::string error;
    bool foundError;
    std::string line;
    std::string errorName;
    std::string oFilename; 
    static const std::map <std::string, int64_t> regNames;
    vector <std::string> lables;
    std::string filename;
    bool checkFilename();
    bool checkBegin();
    bool unpackVariables();
    void unpackLables();
    bool findIncorrectSections();
    bool findStart();
    bool findCheckCommands();
    bool checkContainers();
    
public:
    bool checkFile();
    Validator(std::string filename);
    void printErrorMessage();
    bool validatingError();
    std::string returnOutFileName();
};


#endif