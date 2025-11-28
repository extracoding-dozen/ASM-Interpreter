//
// Created by daniil on 10/31/24.
//

#include "RegisterBlock.h"
#include <iostream>
#include <variant>
#include <any>

void RegisterBlock::setRegister(std::string name, int64_t value) {
    int index;
    index = regNames.at(name);
    //std::cout << index << " " << name << std::endl;
    tumbles[index] = 0;
    blockInt[index] = value;
}

void RegisterBlock::setRegister(std::string name, double value) {
    tumbles[(int) regNames.at(name)] = 1;
    blockDouble[(int) regNames.at(name)] = value;
}

RegisterBlock::RegisterBlock(void): blockInt(DynMemory<int64_t>(17))
                                    , blockDouble(DynMemory<double>(17))
                                    , tumbles(DynMemory<int>(17)) {
}

std::any RegisterBlock::getRegister(const std::string name) {
    int index = regNames.at(name);
    if (!tumbles[index]) {
        std::any result = std::make_any<int64_t &>(blockInt[index]);
        return result;
    }
    std::any result = std::make_any<double &>(blockDouble[index]);
    return result;
}


const std::map <std::string, int64_t> RegisterBlock::regNames = {
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


RegisterBlock::~RegisterBlock() {
}

RegisterBlock::RegisterBlock(const RegisterBlock & other) {
    blockInt = other.blockInt;
    blockDouble = other.blockDouble;
    tumbles = other.tumbles;
}

RegisterBlock & RegisterBlock::operator=(const RegisterBlock& other) {
    blockDouble = other.blockDouble;
    blockInt = other.blockInt;
    tumbles = other.tumbles;
    return *this;
}

/*
std::any RegisterBlock::getRegister(const std::string name) const {
    int index = regNames.at(name);
    if (tumbles[index]) {
        std::any result = std::make_any<double>(blockInt[index]);
        return result;
    }
    std::any result = std::make_any<int64_t>(blockDouble[index]);
    return result;
}
l*/
