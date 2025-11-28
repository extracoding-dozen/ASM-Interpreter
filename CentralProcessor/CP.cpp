#include "CP.h"
#include "Validator/validator.h"
#include <filesystem>
Processor::Processor(): cores(vector<Core>(8) = {Core(), Core(), Core(), Core(), Core(), Core(), Core(), Core()}) {
}

void Processor::executeNew(std::string nameOfFile, int64_t core, std::string mode) {
    if (mode != "linear" && mode != "step by step") {
        throw std::invalid_argument("this mode is incorrect");
    }
    Validator v(nameOfFile);
    if (v.checkFile()) {
        cores[core].createPprog(v.returnOutFileName());
        cores[core].execute(mode);
    }
    else {
        v.printErrorMessage();
    }
    if (std::filesystem::exists(v.returnOutFileName()))
        ;//system("rm .*.sval");
}
/*
Processor::~Processor() {
    for (int i = 0; i < cores.size(); i++) {
        cores[i].~Core();
    }
    cores.~vector();
}
*/
Processor::~Processor(){};