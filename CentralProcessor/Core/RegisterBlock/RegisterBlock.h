#ifndef REGISTERBLOCK_H
#define REGISTERBLOCK_H

#include <cstdint>
#include <map>
#include <stdexcept>
#include <algorithm>
#include <any>
#include "../DynMemory/DynMemory.h"
#include <iostream>

//#include "../../../Printer/Printer.h"

class RegisterBlock {
    DynMemory<int64_t> blockInt;
    DynMemory<double> blockDouble;
    DynMemory<int> tumbles;
    /**
     * @brief A map of assembly register names to their corresponding indices.
     *
     * The following registers are included:
     * - **General-Purpose Registers**:
     *   - AX: Accumulator Register
     *   - BX: Base Register
     *   - CX: Counter Register
     *   - DX: Data Register
     *   - SI: Source Index Register
     *   - DI: Destination Index Register
     *   - BP: Base Pointer Register
     *   - SP: Stack Pointer Register
     *
     * - **Flag Registers**:
     *   - CF: Carry Flag
     *   - PF: Parity Flag
     *   - AF: Adjust Flag
     *   - ZF: Zero Flag
     *   - SF: Sign Flag
     *   - TF: Trap Flag
     *   - IF: Interrupt Enable Flag
     *   - DF: Direction Flag
     *   - OF: Overflow Flag
     *
     * Each register is represented as a key-value pair in the map, where the key is the
     * register name (as a string) and the value is its corresponding index (as an int64_t).
     */
    static const std::map<std::string, int64_t> regNames; 

public:
    /**
     * @brief Sets the value of a register identified by its name.
     *
     * This overload allows setting the register value using an integer.
     *
     * @param name The name of the register to set.
     * @param value The integer value to set the register to.
     */
    void setRegister(std::string name, int64_t value);

    /**
     * @brief Sets the value of a register identified by its name.
     *
     * This overload allows setting the register value using a double.
     *
     * @param name The name of the register to set.
     * @param value The double value to set the register to.
     */
    void setRegister(std::string name, double value);

    /**
     * @brief Constructs a RegisterBlock object.
     *
     * This constructor initializes the RegisterBlock instance.
     */
    RegisterBlock();
    RegisterBlock(const RegisterBlock &);
    ~RegisterBlock();

    /**
     * @brief Gets a reference to the value of a register identified by its name.
     *
     * This function returns a reference to the register value, allowing modification.
     *
     * @param name The name of the register to retrieve.
     * @return A reference to the register value as a double.
     * @throw std::out_of_range If the register with the specified name does not exist.
     */
    std::any getRegister(const std::string name);

    //std::any getRegister(const std::string name) const;
    bool find_name(std::string);

    friend std::ostream& operator <<(std::ostream&os, RegisterBlock & rb) {
        for (auto it = regNames.begin(); it != regNames.end(); it++) {
            try {
                int64_t var = std::any_cast<int64_t>(rb.getRegister(it -> first));
                std::cout << it -> first << ": " <<  var << std::endl;
            }
            catch (...) {
                std::cout << it -> first << ": " << std::any_cast<double>(rb.getRegister(it -> first)) << std::endl;
            }
        }
        return os;
    }
    RegisterBlock & operator=(const RegisterBlock&);
};

#endif //REGISTERBLOCK_H
/*

PrintStr : Print<Str> {


    print(const& std::string str) {
        логика
    }

}

friend operator << (const& std::string str) {



}
*/