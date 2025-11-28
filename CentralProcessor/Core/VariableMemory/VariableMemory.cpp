//
// Created by daniil on 10/31/24.
//

#include "VariableMemory.h"

#include <stdexcept>

void VariableMemory::setVariable(std::string variableName, int64_t variableValue) {
    if (variables.find(variableName) != variables.end()) {
        variables[variableName] = variableValue;
    } else {
    variables[variableName] = std::make_any<int64_t>(variableValue);
    }
}


void VariableMemory::setVariable(std::string variableName, double variableValue) {
    if (variables.find(variableName) != variables.end()) {
        variables[variableName] = variableValue;
    } else {
        variables[variableName] = std::make_any<double>(variableValue);
    }
}

std::any &VariableMemory::getVariable(std::string variableName) {
    return variables.at(variableName);
}

std::map <std::string, std::any> VariableMemory::variables;

VariableMemory::VariableMemory(const VariableMemory & other) {
    variables = other.variables;
}
VariableMemory & VariableMemory::operator=(const VariableMemory & other) {
    if (this != &other) {
        variables = other.variables;
    }
    return *this;
}

VariableMemory::VariableMemory() {
}