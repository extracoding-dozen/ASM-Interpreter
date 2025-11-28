#ifndef CP_H
#define CP_H

//#include "Core/DynMemory/DynMemory.h"
#include "Core/Core.h"
#include <vector>
using std::vector;

class Processor {
private:
    vector <Core> cores;
public:
    Processor();
    //void addCore(Core);
    void executeNew(std::string nameOfFile, int64_t core, std::string mode = "linear");
    ~Processor();

};


#endif