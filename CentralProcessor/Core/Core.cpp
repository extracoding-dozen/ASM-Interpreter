#include "Core.h"

Core::Core(): rb(RegisterBlock()), 
            vm(VariableMemory()),
            prog(Programm()){}

void Core::execute(std::string mode) {
    prog.executeProgramm(rb, vm, mode);
}


void Core::createPprog(std::string nameOfFile) {
    prog.makeProgramm(rb, vm, nameOfFile);
}


Core::Core(const Core & other) {
    rb = other.rb;
}

Core & Core::operator=(const Core & other) {   
    if (&other != this)
        rb = other.rb;
    return *this;
}