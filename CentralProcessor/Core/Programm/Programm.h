#ifndef PROGRAMM_H
#define PROGRAMM_H

#include "Command.h"
#include "Add/Add.h"
#include "Mult/Mult.h"
#include "Mov/Mov.h"
#include "../RegisterBlock/RegisterBlock.h"
#include "../VariableMemory/VariableMemory.h"
#include <tuple>
#include <memory>
#include <vector>
#include <map>

using std::vector;

/**
 * @brief Class representing a program that manages and executes a sequence of commands.
 *
 * The `Programm` class is responsible for storing commands, managing labels, and executing
 * the commands in the correct order. It interacts with `RegisterBlock` and `VariableMemory`
 * to perform operations defined by the commands.
 */
class Programm {
private:
    /// A vector of tuples containing shared pointers to command objects and their associated operands.
    vector<std::tuple<std::shared_ptr<CommandConcretic>, std::string, std::string>> prog;

    /// A list of command names for reference or execution.
    vector<std::string> cmdlist;

    /// A map of labels to their corresponding instruction indices.
    std::map<std::string, int64_t> lables;

    /**
     * @brief Adds a command to the program.
     *
     * This private method stores a command along with its operands in the program's command list.
     *
     * @param cmd A shared pointer to the command to be added.
     * @param operand1 The first operand associated with the command.
     * @param operand2 The second operand associated with the command.
     */
    void pushCommand(std::shared_ptr<CommandConcretic> cmd, std::string operand1, std::string operand2);

    /**
     * @brief Sets a label for a specific command index.
     *
     * This private method associates a label name with a command index in the program.
     *
     * @param name The name of the label to be set.
     * @param index The index of the command associated with the label.
     */
    void setLable(std::string name, int64_t index);

    /**
     * @brief Executes the next command in the program.
     *
     * This private method retrieves and executes the next command in the sequence,
     * using the provided `RegisterBlock` and `VariableMemory`.
     *
     * @param rb The register block to be used during command execution.
     * @param vm The variable memory to be used during command execution.
     */
    void exexuteNext(RegisterBlock & rb, VariableMemory & vm);

public:
    /**
     * @brief Constructs a new Programm object.
     */
    Programm();

    /**
     * @brief Destroys the Programm object.
     */
    ~Programm() {};

    /**
     * @brief Copy assignment operator for the Programm class.
     *
     * @param other The other Programm object to copy from.
     * @return A reference to this Programm object.
     */
    Programm & operator=(const Programm & other);

    /**
     * @brief Copy constructor for the Programm class.
     *
     * @param other The other Programm object to copy from.
     */
    Programm(const Programm & other);

    /**
     * @brief Creates a program from a specified file.
     *
     * This method reads commands from a file and initializes the program with them.
     *
     * @param rb The register block to be used by the program.
     * @param vm The variable memory to be used by the program.
     * @param filename The name of the file containing the program commands.
     */
    void makeProgramm(RegisterBlock & rb, VariableMemory & vm, std::string filename);

    /**
     * @brief Executes the program in the specified mode.
     *
     * This method runs the commands in the program using the provided resources.
     *
     * @param rb The register block to be used during execution.
     * @param vm The variable memory to be used during execution.
     * @param mode The mode in which to execute the program (e.g., step-by-step or full execution).
     */
    void executeProgramm(RegisterBlock & rb, VariableMemory & vm, std::string mode);
};

#endif // PROGRAMM_H