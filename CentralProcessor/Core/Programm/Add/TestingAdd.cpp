#include <gtest/gtest.h>
#include <any>
#include <string>
#include "../../RegisterBlock/RegisterBlock.h"
#include "../../VariableMemory/VariableMemory.h"
#include "Add.h"


// Test cases
TEST(AddTest, AddsTwoIntegersFromRegisters) {
    RegisterBlock rb;
    VariableMemory wm;
    Add add;

    // Set up initial values in the RegisterBlock
    rb.setRegister("AX", int64_t(5));
    rb.setRegister("BX", int64_t(10));
    
    std::string operand1 = "AX";
    std::string operand2 = "BX";

    add.whatToDo(rb, wm, operand1, operand2);

    // Check the result
    EXPECT_EQ(std::any_cast<int64_t>(rb.getRegister(operand1)), 15); // reg1 should now hold 15
}

TEST(AddTest, AddsIntegerFromRegisterAndDoubleFromVariableMemory) {
    RegisterBlock rb;
    VariableMemory wm;
    Add add;

    // Set up initial values in the RegisterBlock and VariableMemory
    rb.setRegister("DX", int64_t(5));
    wm.setVariable("var1", double(3.5));
    
    std::string operand1 = "DX";
    std::string operand2 = "var1";

    add.whatToDo(rb, wm, operand1, operand2);

    // Check the result
    EXPECT_EQ(std::any_cast<double>(rb.getRegister(operand1)), 8.5); // reg1 should now hold 8.5
}

TEST(AddTest, HandlesVariableMemoryWhenRegisterFails) {
    RegisterBlock rb;
    VariableMemory wm;
    Add add;

    // Set up initial values in the VariableMemory
    wm.setVariable("var1", int64_t(7));
    wm.setVariable("var2", double(2.5));

    std::string operand1 = "var1";
    std::string operand2 = "var2";

    add.whatToDo(rb, wm, operand1, operand2);

    // Check the result
    EXPECT_EQ(std::any_cast<double>(wm.getVariable(operand1)), 9.5); // var1 should now hold 9.5
}

TEST(AddTest, HandlesBothOperandsFromVariableMemory) {
    RegisterBlock rb;
    VariableMemory wm;
    Add add;

    // Set up initial values in the VariableMemory
    wm.setVariable("var1", int64_t(3));
    wm.setVariable("var2", int64_t(4));

    std::string operand1 = "var1";
    std::string operand2 = "var2";

    add.whatToDo(rb, wm, operand1, operand2);

    // Check the result
    EXPECT_EQ(std::any_cast<int64_t>(wm.getVariable(operand1)), 7); // var1 should now hold 7
}


// Additional Test Cases
TEST(AddTest, AddsTwoDoublesFromRegisters) {
    RegisterBlock rb;
    VariableMemory wm;
    Add add;

    // Set up initial values in the RegisterBlock
    rb.setRegister("BX", double(5.5));
    rb.setRegister("CX", double(4.5));
    
    std::string operand1 = "BX";
    std::string operand2 = "CX";

    add.whatToDo(rb, wm, operand1, operand2);

    // Check the result
    EXPECT_EQ(std::any_cast<double>(rb.getRegister(operand1)), 10.0); // reg1 should now hold 10.0
}


TEST(AddTest, AddDoubleFromRegisterAndInt) {
    RegisterBlock rb;
    VariableMemory wm;
    Add add;

    // Set up initial values in the RegisterBlock
    rb.setRegister("BX", double(5.5));
    
    std::string operand1 = "BX";
    std::string operand2 = "4.5";
    add.whatToDo(rb, wm, operand1, operand2);

    // Check the result
    EXPECT_EQ(std::any_cast<double>(rb.getRegister(operand1)), 10.0); // reg1 should now hold 10.0
}


TEST(AddTest, HandlesAddingNonExistentRegister) {
    RegisterBlock rb;
    VariableMemory wm;
    Add add;

    // Set up initial value in VariableMemory
    wm.setVariable("var1", int64_t(5));
    
    std::string operand1 = "non_existent_reg";
    std::string operand2 = "var1";

    // Attempt to add a non-existent register
    EXPECT_THROW({
        add.whatToDo(rb, wm, operand1, operand2);
    }, std::out_of_range); // Expect an exception for the non-existent register
}

TEST(AddTest, AddsTwoVariablesFromVariableMemory) {
    RegisterBlock rb;
    VariableMemory wm;
    Add add;

    // Set up initial values in VariableMemory
    wm.setVariable("var1", int64_t(3));
    wm.setVariable("var2", int64_t(4));

    std::string operand1 = "var1";
    std::string operand2 = "var2";

    add.whatToDo(rb, wm, operand1, operand2);

    // Check the result
    EXPECT_EQ(std::any_cast<int64_t>(wm.getVariable(operand1)), 7); // var1 should now hold 7
}

TEST(AddTest, AddsDoubleToIntegerInVariableMemory) {
    RegisterBlock rb;
    VariableMemory wm;
    Add add;

    // Set up initial values in VariableMemory
    wm.setVariable("var1", int64_t(10));
    wm.setVariable("var2", double(5.5));

    std::string operand1 = "var1";
    std::string operand2 = "var2";

    add.whatToDo(rb, wm, operand1, operand2);

    // Check the result
    EXPECT_EQ(std::any_cast<double>(wm.getVariable(operand1)), 15.5); // var1 should now hold 15.5
}

TEST(AddTest, AddsNegativeValues) {
    RegisterBlock rb;
    VariableMemory wm;
    Add add;

    // Set up initial values in RegisterBlock
    rb.setRegister("AX", int64_t(-5));
    rb.setRegister("BX", int64_t(-10));
    
    std::string operand1 = "AX";
    std::string operand2 = "BX";

    add.whatToDo(rb, wm, operand1, operand2);

    // Check the result
    EXPECT_EQ(std::any_cast<int64_t>(rb.getRegister(operand1)), -15); // reg1 should now hold -15
}

TEST(AddTest, AddsOverflow) {
    RegisterBlock rb;
    VariableMemory wm;
    Add add;

    // Set up initial values in RegisterBlock
    rb.setRegister("AX", int64_t(INT64_MAX));
    rb.setRegister("BX", int64_t(1));
    
    std::string operand1 = "AX";
    std::string operand2 = "BX";

    add.whatToDo(rb, wm, operand1, operand2);

    // Check the result
    EXPECT_EQ(std::any_cast<int64_t>(rb.getRegister("OF")), 1); // reg1 should now hold -15
}


// Main function for running tests
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
/*

int main() {
    RegisterBlock rb;
    VariableMemory wm;
    Add add;

    // Set up initial values in the RegisterBlock
    rb.setRegister("BX", double(5.5));
    
    std::string operand1 = "BX";
    std::string operand2 = "4.5";
    add.whatToDo(rb, wm, operand1, operand2);

    // Check the result
    EXPECT_EQ(std::any_cast<double>(rb.getRegister(operand1)), 10.0); // reg1 should now hold 10.0

}
*/