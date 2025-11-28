#include "validator.h"
#include <filesystem>
#include <sstream>
#include <iostream>
#include "../Constants/Constants.h"
#include <stdexcept>
#include <algorithm>
#include <thread>
#include <cmath>
#include <mutex>


std::mutex mtx;

void printVector(const vector <std::string> v) {
    for (auto elem : v) {
        std::cout << colours::GREEN << "\"" + elem + "\" "; 
    }
    std::cout << std::endl << colours::RESET;
}

std::string convertVarCommand(const std::string & source) {
    std::string repos = "    ";
    std::istringstream iss(source);
    std::string word;
    while (iss >> word) {
        if (word != "\t")
            repos += word + ' ';
    }
    return repos;
}

std::string convertSection(const std::string & source) {
    std::string repos = "";
    std::istringstream iss(source);
    std::string word;
    while (iss >> word) {
        if (word != "\t")
            repos += word + ' ';
    }
    return repos;
}


const std::map <std::string, int64_t> Validator::regNames = {
    // Basic registers
    {"AX", 0}, ///< Accumulator Register
    {"BX", 1}, ///< Base Register
    {"CX", 2}, ///< Counter Register
    {"DX", 3}, ///< Data Register
    {"SI", 4}, ///< Source Index Register
    {"DI", 5}, ///< Destination Index Register
    {"BP", 6}, ///< Base Pointer Register
    {"SP", 7}, ///< Stack Pointer Register
    // Flag registers
    {"CF", 8}, ///< Carry Flag
    {"PF", 9}, ///< Parity Flag
    {"AF", 10}, ///< Adjust Flag
    {"ZF", 11}, ///< Zero Flag
    {"SF", 12}, ///< Sign Flag
    {"TF", 13}, ///< Trap Flag
    {"IF", 14}, ///< Interrupt Enable Flag
    {"DF", 15}, ///< Direction Flag
    {"OF", 16} ///< Overflow Flag
};

Validator::Validator(std::string name): filename(name) 
                            , variables(vector <std::string> (0))
                            , lables (vector <std::string> (0)) 
                            , errorName("correct") {};

bool Validator::checkFilename() {
    //std::regex namePattern(".*\\.s$");
    if (!std::regex_match(filename, patterns::filenamePattern)) {
        errorName = "file is not a asm code\n";
        return false;
    }
    if (!std::filesystem::exists(filename)) {
        errorName = "file does not exist\n";
        return false;
    }
    return true;
}

bool Validator::checkBegin() {
    //std::string line;
    std::lock_guard <std::mutex> lock(mtx);
    std::getline(source, line);
    while (std::regex_match(line, patterns::spaceLinePattern)) std::getline(source, line);
    if (!(std::regex_match(line, patterns::sectionDataPattern) || std::regex_match(line, patterns::startPattern))) {
        error = line;
        return true;
    }
    repos << convertSection(line) << std::endl;
    return false;
}


bool Validator::unpackVariables() {
    //std::string line;
    //std::regex patternVarB(R"(^\s*([a-zA-Z_][a-zA-Z0-9_]*)\s+db\s+(-?\d+(\.\d+)?)$)");
    //std::regex spacePetterned(R"(^\s*$)");
    std::getline(source, line);
    while (std::regex_match(line, patterns::variableLinePattern)) {
        std::istringstream sin(line);
        std::string name;
        sin >> name;
        variables.push_back(name);
        repos << convertVarCommand(line) << std::endl;
        getline(source, line);
    }
    if (line != "" && !std::regex_match(line, patterns::startPattern) && !std::regex_match(line, patterns::spaceLinePattern)) {
        error = line;
        return true;
    }
    else {
        if (!std::regex_match(line, patterns::spaceLinePattern)) repos << convertSection(line);
        repos << std::endl;
    }
    return false;
}


void Validator::unpackLables() {
    std::ifstream fin(filename);
    std::string line;
    //std::regex lablePattern("^[a-z]+:$");
    while (getline(fin, line)) {
        if (std::regex_match(line, patterns::lablePattern)) {
            lables.push_back(line);
        }
    }
}


bool Validator::findIncorrectSections() {
    std::ifstream fin(filename);
    std::string line;
    //std::regex patternSection("^section +\\.[a-z]+$");
    while (getline(fin, line)) {
        if (std::regex_match(line, patterns::sectionPattern)) {
            std::istringstream iss(line);
            std::string _, name;
            iss >> _ >> name;
            if (name != ".data") {
                error = line;
                return false;
            }
        }
    }
    return true;
}

vector <std::string> commands = {"mov", "jmp", "mult", "add"};

bool Validator::findCheckCommands() {
    /*
    std::string pattline = "(";
    for (int i = 0; i < commands.size(); i++) {
        pattline += commands[i];
        if (i != commands.size() - 1) {
            pattline += '|';
        }
    }
    pattline += ')';
    std::regex commandPattern("^\\s*" + pattline + " +([a-zA-Z_][a-zA-Z0-9_]*) *, *(\\d+(\\.\\d+)?|[a-zA-Z_][a-zA-Z0-9_]*)$");
    //std::string line;
    */
    if (!std::regex_match(line, patterns::sectionDataPattern)) {
        while (!std::regex_match(line, patterns::startPattern) && getline(source, line)) {
            if (line != "") break;
        }
        if (!std::regex_match(line, patterns::startPattern)) {
            error = line;
            errorName = "this line is not a correct command or section\n > ";
            return false;
        }
        else repos << convertSection(line) << std::endl;
    }
    while (getline(source, line)) {
        if (line != "") {
            if (std::regex_match(line, patterns::commandPattern) || std::regex_match(line, patterns::lablePattern)) {
                repos << convertVarCommand(line) << std::endl;
                std::string saved = line;
                for (int i = 0; i < line.size(); i++) {
                    if (line[i] == ',') line[i] = ' ';
                }
                if (!std::regex_match(line, patterns::lablePattern)) {
                    std::istringstream iss(line);
                    std::string cmdName, cmdArg1, cmdArg2;
                    iss >> cmdName >> cmdArg1 >> cmdArg2;
                    if (std::find(variables.begin(), variables.end(), cmdArg1) == variables.end()) {
                        try {
                            regNames.at(cmdArg1);
                        } catch(...) {
                            errorName = "first argument is not a variable or register \n> ";
                            error = line;
                            return false;
                        }
                    }
                    if (std::find(variables.begin(), variables.end(), cmdArg2) == variables.end()) {
                        try {
                            regNames.at(cmdArg2);
                        } catch(...) {
                            try {
                                stod(cmdArg2);
                            } catch(...) {
                                error = line;
                                printVector(variables);
                                //std::cout << cmdArg2 << std::endl;
                                errorName = "second argument is not a variable, register, integer or float value \n> ";
                                return false;
                            }
                        }
                    }
                }
            }
            else {
                errorName = "line is not correct command or lable \n> ";
                error = line;
                return false;
            }
        }
    }
    return true;
}

namespace keys {
    std::map <std::string, int> pairs{
        {"name", 2},
        {"begin", 3}, 
        {"variables", 5}, 
        {"sections", 7}
    };
};

bool Validator::checkFile() {
    foundError = false;
    if (!checkFilename()) {
        return false;
    }
    source = std::ifstream(filename);
    oFilename = '.' + filename + "val";
    repos = std::ofstream(oFilename);
    int variant = 1;
    std::thread beg([&variant, this]() {
        variant *= static_cast <int> (pow(keys::pairs["begin"], static_cast <int> (checkBegin())));
    });
    beg.join();
    std::thread vars([&variant, this]() {
        variant *= static_cast <int> (pow(keys::pairs["variables"], static_cast <int> (unpackVariables())));
    });

    std::thread sects([&variant, this]() {
        variant *= static_cast <int> (pow(keys::pairs["sections"], static_cast <int> (!findIncorrectSections())));
    });
    std::thread lables([this]() {unpackLables();});
    /*
    if (checkBegin()) {
        errorName = "incorrect begining of file \n> ";
        foundError = true;
        return false;
    }
    //std::cout << "*" <<std::endl;
    if (unpackVariables()) 
    {
        errorName = "incorrect variable name \n> ";
        foundError = true;
        return false;
    }
    //std::cout << "**" <<std::endl;
    //std::cout << "***" <<std::endl;
    if (!findIncorrectSections()) {
        errorName = "found incorrect section \n> ";
        foundError = true;
        return false;
    }
    //std::cout << "****" <<std::endl;
    */
    vars.join();
    sects.join();
    lables.join();
    if (variant != 1) {
        if (variant % 3 == 0) {
            errorName = "incorrect begining of file \n> ";
            foundError = true;
            return false;
        }
        else if (variant % 5 == 0) {
            errorName = "incorrect variable name \n> ";
            foundError = true;
            return false;
        }
        else {
            errorName = "found incorrect section \n> ";
            foundError = true;
            return false;
        }
    }
    if (!findCheckCommands()) {
        foundError = true;
        return false;
    }
    //std::cout << "*" <<std::endl;
    return true;
}





void Validator::printErrorMessage() {
    std::cout << colours::YELLOW << "Compilation error\n";
    std::cout << errorName;
    std::cout << colours::RED << "\"" + error + "\"" << colours::RESET << std::endl;
}


std::string Validator::returnOutFileName() {
    return oFilename;
}

bool Validator::validatingError() {
    return foundError;
}