#ifndef CORE_H
#define CORE_H

#include "Programm/Programm.h"
#include <iostream>
class Core {
private:
    RegisterBlock rb;
    VariableMemory vm;
    Programm prog;
public:
    void execute(std::string mode);
    void createPprog(std::string nameOfFile);
    Core();
    friend std::ostream& operator << (std::ostream & os, Core & c) {
        os << c.rb << c.vm;
        return os;
    }
    Core(const Core &);
    Core & operator=(const Core &);
    ~Core(){};
};

#endif