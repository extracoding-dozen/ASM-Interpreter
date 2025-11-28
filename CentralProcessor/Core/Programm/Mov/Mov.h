#ifndef MOV_H
#define MOV_H

#include "../Command.h"
#include <string>
#include <algorithm>

class Mov : public Command <RegisterBlock&, VariableMemory&, std::string&, std::string&>, public CommandConcretic {
public:
    void whatToDo (RegisterBlock& rb, VariableMemory& wm, std::string& operand1, std::string& operand2) override {
        std::any val1;
        try {
            val1 = rb.getRegister(operand1);
        } catch (...) {
            val1 = wm.getVariable(operand1);
        }
        std::any val2;
        try {
            if (operand2.find('.') != std::string::npos) {
                val2 = std::stod(operand2);
            }
            else {
                val2 = static_cast<int64_t>(std::stoi(operand2));
            }
            goto sum;
        } catch(...){};

        try {
            val2 = rb.getRegister(operand2);
        } catch (...) {
            val2 = wm.getVariable(operand2);
        }
        sum:
        int64_t oper1i = 0;
        double oper1d = 0;
        try {
            oper1i = std::any_cast<int64_t>(val1);
        } catch(...) {
            oper1i = 0;
            oper1d = std::any_cast<double>(val1);
        }
        int64_t oper2i = 0;
        double oper2d = 0;
        try {
            oper2i = std::any_cast<int64_t>(val2);
        } catch(...) {
            oper2i = 0;
            oper2d = std::any_cast<double>(val2);
        }
        if (oper2d == 0) {
            try {
                rb.setRegister(operand1, oper2i);
            }
            catch (...) {
                wm.setVariable(operand1, oper2i);
            }
        }
        else {
            try {
                rb.setRegister(operand1, oper2d);
            }
            catch (...) {
                wm.setVariable(operand1, oper2d);
            }
        }
    }
};

#endif