#include "CP.h"
#include "Validator/validator.h"


int main() {
    Processor p;
    /*
    Core c;
    c.createPprog("input.s");
    c.execute("step_by_step");
    Validator v("input.s");
    if (!v.checkFile()) {
        v.printErrorMessage();
    }
    */
    p.executeNew("input.s", 0, "step by step");

}