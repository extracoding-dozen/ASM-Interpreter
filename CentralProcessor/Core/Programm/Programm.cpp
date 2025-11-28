#include "Programm.h"
#include <fstream>
#include <sstream>
#include <map>
#include <memory>
#include <iostream>
#include <regex>
#include <cstdlib>
#include "../../Constants/Constants.h"

namespace cmd {
    std::map <std::string, std::shared_ptr<CommandConcretic>> cmdList = {
        {"add", std::make_shared<Add>()},
        {"mult", std::make_shared<Mult>()},
        {"mov", std::make_shared<Mov>()}
        //{"jmp", Jmp()},
    };
}

void Programm::pushCommand(std::shared_ptr<CommandConcretic> cmd, std::string operand1, std::string operand2) {
    prog.push_back(std::make_tuple(cmd, operand1, operand2));
}



void Programm::exexuteNext(RegisterBlock & rb, VariableMemory & vm) {
    int64_t index = std::any_cast<int64_t>(rb.getRegister("SP"));
    std::string operand1 = std::get<1>(prog[(index)]);
    std::string operand2 = std::get<2>(prog[index]);
    //std::cout << rb << vm << operand1 << ' ' << operand2 << std::endl; 
    std::get<0>(prog[index]) -> whatToDo(rb, vm, operand1, operand2);
    rb.setRegister("SP", index + 1);
}


void Programm::setLable(std::string name, int64_t index) {
    if (lables.find(name) != lables.end()) {
        throw std::out_of_range("Argument is incorrect");
    }
    lables[name] = index + 1;
}


void Programm::makeProgramm(RegisterBlock & rb, VariableMemory & vm, std::string filename) {
    std::ifstream fin(filename);
    std::string cmdline;
    getline(fin, cmdline);
    //std::cout << "first " << cmdline <<std::endl;
   // std::regex pattern("^[a-zA-Z_]+:$");
    //std::regex patternVarB(R"(^\s*([a-zA-Z_][a-zA-Z0-9_]*)\s+db\s+(-?\d+(\.\d+)?)$)");
    if (std::regex_match(cmdline, patterns::startPattern)) goto start;
    if (std::regex_match(cmdline, patterns::sectionDataPattern)) {
        //std::cout << "love\n";
        getline(fin, cmdline);
        while (cmdline != "" && std::regex_match(cmdline, patterns::variableLinePattern)) {
            std::istringstream sin(cmdline);
            std::string name, _, val;
            sin >> name >> _ >> val;
            //std::cout << name << ' ' << _ << "variable is " << val <<std::endl;
            if (val.find('.') != std::string::npos)
                vm.setVariable(name, stod(val));
            else 
                vm.setVariable(name, static_cast<int64_t>(stoi(val)));
            //std::cout << "varblock " << cmdline << std::endl;
            getline(fin, cmdline);

        }
        while (!std::regex_match(cmdline, patterns::startPattern)) {
            getline(fin, cmdline);
            //std::cout << "trash " << cmdline << std::endl;

        }
        start:
        int64_t index = 0;
        while (getline(fin, cmdline)) {
            cmdlist.push_back(cmdline);
            //std::cout << "programm " << cmdline << std::endl;
            if (std::regex_match(cmdline, patterns::lablePattern)) {
                setLable(cmdline, index);
                continue;
            }
            if (cmdline.find(',') != std::string::npos) {
                cmdline[cmdline.find(',')] = ' ';
            }
            std::istringstream sin(cmdline);
            //cmdlist.push_back(cmdline);
            std::string name, oper1, oper2;
            sin >> name >> oper1 >> oper2;
            //std::cout << name << ' ' << oper1 << ' ' << oper2 << '\n';
            pushCommand(cmd::cmdList[name], oper1, oper2);
        }
    }
}


void Programm::executeProgramm(RegisterBlock & rb, VariableMemory & vm, std::string mode) {
    rb.setRegister("SP", static_cast <int64_t>(0));
    for (; std::any_cast<int64_t>(rb.getRegister("SP")) < static_cast<int64_t>(prog.size());) {
        if (mode == "step by step") {
            std::cout << rb << std::endl << vm << std::endl;
            std::cout << cmdlist[std::any_cast<int64_t>(rb.getRegister("SP"))] << "\n\n";
            std::cin.clear();
            std::string _;
            std::getline(std::cin, _);
            system("clear");
            //std::cin.get();
        }
        exexuteNext(rb, vm);
    }
    system("clear");
    std::cout << rb << std::endl << vm << std::endl;
}

Programm::Programm(): prog(vector<std::tuple<std::shared_ptr<CommandConcretic>, std::string, std::string>>(static_cast<int64_t>(0)))
                    , cmdlist(vector<std::string>(0)){};


Programm & Programm::operator=(const Programm & other) {
    cmdlist = other.cmdlist;
    lables = other.lables;
    prog = other.prog;
    return *this;
}

Programm::Programm(const Programm & other) {
    cmdlist = other.cmdlist;
    lables = other.lables;
    prog = other.prog;
}