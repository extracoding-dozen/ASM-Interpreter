//
// Created by daniil on 10/31/24.
//

#ifndef VARIABLEMEMORY_H
#define VARIABLEMEMORY_H

#include <map>
#include <string>
#include <any>
#include <iostream>

/**
 * @class VariableMemory
 * @brief A class that provides a simple variable storage mechanism using a map.
 *
 * The VariableMemory class allows you to store and retrieve variables of different types
 * (currently int64_t and double) using a string as the key. It utilizes std::any to store
 * the values, providing flexibility in the types of variables that can be stored.
 */
class VariableMemory {
    static std::map<std::string, std::any> variables; ///< A map to store variable names and their values.

public:
    /**
     * @brief Sets a variable with an int64_t value.
     *
     * This function stores the specified integer value under the given variable name.
     * If a variable with the same name already exists, it will be overwritten.
     *
     * @param name The name of the variable to set.
     * @param value The int64_t value to assign to the variable.
     */
    void setVariable(std::string name, int64_t value);

    /**
     * @brief Sets a variable with a double value.
     *
     * This function stores the specified double value under the given variable name.
     * If a variable with the same name already exists, it will be overwritten.
     *
     * @param name The name of the variable to set.
     * @param value The double value to assign to the variable.
     */
    void setVariable(std::string name, double value);

    /**
     * @brief Retrieves a variable by name.
     *
     * This function returns a reference to the variable stored under the given name.
     * If the variable does not exist, it will throw an exception. It is the caller's
     * responsibility to ensure that the variable exists before calling this function.
     *
     * @param name The name of the variable to retrieve.
     * @return A reference to the std::any object containing the variable's value.
     */
    std::any &getVariable(std::string name);
    friend std::ostream& operator <<(std::ostream&os, VariableMemory & vm) {
        for (auto elem : vm.variables) {
            try {
                int64_t var = std::any_cast<int64_t>(std::get<1>(elem));
                std::cout <<  std::get<0>(elem) << ": " <<  var << std::endl;
            }
            catch (...) {

                std::cout <<  std::get<0>(elem) << ": " << std::any_cast<double>(std::get<1>(elem)) << std::endl;
            }
        }
        return os;
    }
    VariableMemory(const VariableMemory &);
    VariableMemory();
    VariableMemory & operator=(const VariableMemory &);
};

#endif //VARIABLEMEMORY_H