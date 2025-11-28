//
// Created by daniil on 10/31/24.
//

#ifndef COMMAND_H
#define COMMAND_H

#include "../RegisterBlock/RegisterBlock.h"
#include "../VariableMemory/VariableMemory.h"
#include <string>
#include <functional>

/**
 * @brief Abstract base class representing a command with a variable number of arguments.
 *
 * This class serves as a template for creating command objects that can perform
 * actions based on the provided arguments. Derived classes must implement the
 * `whatToDo` method to define specific behavior.
 *
 * @tparam Args Types of the arguments that the command will accept.
 */
template <typename... Args>
class Command {
public:
    /// Virtual destructor for proper cleanup of derived classes.
    virtual ~Command() = default;

    /**
     * @brief Executes the command with the given arguments.
     *
     * This pure virtual function must be implemented by derived classes to
     * define the specific action to be performed when the command is executed.
     *
     * @param args The arguments to be passed to the command.
     */
    virtual void whatToDo(Args... args) = 0;
};

/**
 * @brief Abstract base class for concrete command implementations.
 *
 * This class defines a command that operates on a `RegisterBlock` and
 * `VariableMemory`. Derived classes must implement the `whatToDo` method
 * to specify the command's behavior using these resources.
 */
class CommandConcretic {
public:
    /// Virtual destructor for proper cleanup of derived classes.
    virtual ~CommandConcretic() = default;

    /**
     * @brief Executes the command using the provided resources.
     *
     * This pure virtual function must be implemented by derived classes to
     * define the specific action to be performed using the given
     * `RegisterBlock` and `VariableMemory`.
     *
     * @param regBlock The register block to be used by the command.
     * @param varMemory The variable memory to be used by the command.
     * @param param1 A string parameter for the command.
     * @param param2 A second string parameter for the command.
     */
    virtual void whatToDo(RegisterBlock&, VariableMemory&, std::string&, std::string&) = 0;
};

#endif //COMMAND_H