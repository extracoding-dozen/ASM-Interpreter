#include <gtest/gtest.h>
#include "Mult.h" 
#include <gtest/gtest.h>
#include <any>
#include <string>
#include "../../RegisterBlock/RegisterBlock.h"
#include "../../VariableMemory/VariableMemory.h"


TEST(MultTest, MultiplyTwoIntegerRegisters_1) {
    RegisterBlock rb;
    VariableMemory wm;
    Mult mult;

    rb.setRegister("AX", static_cast<int64_t>(5));
    rb.setRegister("BX", static_cast<int64_t>(10));

    std::string operand1 = "AX";
    std::string operand2 = "BX";
    mult.whatToDo(rb, wm, operand1, operand2);

    EXPECT_EQ(std::any_cast<int64_t>(rb.getRegister("AX")), 50);
}

TEST(MultTest, MultiplyIntegerRegisterWithDoubleValue_1) {
    RegisterBlock rb;
    VariableMemory wm;
    Mult mult;

    rb.setRegister("AX", static_cast<int64_t>(5));

    std::string operand1 = "AX";
    std::string operand2 = "2.0"; 
    mult.whatToDo(rb, wm, operand1, operand2);

    EXPECT_DOUBLE_EQ(std::any_cast<double>(rb.getRegister("AX")), 10.0);
}

TEST(MultTest, MultiplyTwoDoubleValues_1) {
    RegisterBlock rb;
    VariableMemory wm;
    Mult mult;

    rb.setRegister("AX", static_cast<int64_t>(2));
    rb.setRegister("BX", static_cast<double>(3.5));

    std::string operand1 = "AX";
    std::string operand2 = "BX";
    mult.whatToDo(rb, wm, operand1, operand2);

    EXPECT_DOUBLE_EQ(std::any_cast<double>(rb.getRegister("AX")), 7.0);
}


TEST(MultTest, HandleOverflowWhenMultiplyingTwoIntegers_1) {
    RegisterBlock rb;
    VariableMemory wm;
    Mult mult;

    rb.setRegister("AX", static_cast<int64_t>(INT64_MAX));
    rb.setRegister("BX", static_cast<int64_t>(2));

    std::string operand1 = "AX";
    std::string operand2 = "BX";
    mult.whatToDo(rb, wm, operand1, operand2);

    EXPECT_EQ(std::any_cast<int64_t>(rb.getRegister("OF")), 1); 
}


TEST(MultTest, FirstOperandNotFoundInRegisterBlock_1) {
    RegisterBlock rb;
    VariableMemory wm;
    Mult mult;

    rb.setRegister("AX", static_cast<int64_t>(5)); 
    wm.setVariable("var1", static_cast<int64_t>(5)); 

    std::string operand1 = "reg1"; 
    std::string operand2 = "var1"; 
    EXPECT_THROW(mult.whatToDo(rb, wm, operand1, operand2), std::out_of_range);
    EXPECT_EQ(std::any_cast<int64_t>(wm.getVariable("var1")), 5);
}

TEST(MultTest, SecondOperandNotFoundInRegisterBlock_1) {
    RegisterBlock rb;
    VariableMemory wm;
    Mult mult;

    rb.setRegister("AX", static_cast<int64_t>(10)); 

    std::string operand1 = "AX"; 
    std::string operand2 = "nonexistent"; 
    wm.setVariable("var1", static_cast<int64_t>(5)); 
    EXPECT_EQ(std::any_cast<int64_t>(rb.getRegister("AX")), 10);
    EXPECT_THROW(mult.whatToDo(rb, wm, operand1, operand2), std::out_of_range);
}

TEST(MultTest, MultiplyWithVariableInMemory_1) {
    RegisterBlock rb;
    VariableMemory wm;
    Mult mult;

    rb.setRegister("AX", static_cast<int64_t>(3));
    wm.setVariable("var1", static_cast<int64_t>(4)); 

    std::string operand1 = "AX"; 
    std::string operand2 = "var1"; 
    mult.whatToDo(rb, wm, operand1, operand2);

    EXPECT_EQ(std::any_cast<int64_t>(rb.getRegister("AX")), 12);
}


TEST(MultTest, OverflowWhenMultiplyingLargeIntegers_1) {
    RegisterBlock rb;
    VariableMemory wm;
    Mult mult;

    rb.setRegister("AX", static_cast<int64_t>(INT64_MAX / 2));
    rb.setRegister("BX", static_cast<int64_t>(3));

    std::string operand1 = "AX";
    std::string operand2 = "BX";
    mult.whatToDo(rb, wm, operand1, operand2);

    EXPECT_EQ(std::any_cast<int64_t>(rb.getRegister("OF")), 1);
}

TEST(MultTest, MultiplyNegativeAndPositiveInteger_1) {
    RegisterBlock rb;
    VariableMemory wm;
    Mult mult;

    rb.setRegister("AX", static_cast<int64_t>(-5));
    rb.setRegister("BX", static_cast<int64_t>(10));

    std::string operand1 = "AX";
    std::string operand2 = "BX";
    mult.whatToDo(rb, wm, operand1, operand2);

    EXPECT_EQ(std::any_cast<int64_t>(rb.getRegister("AX")), -50);
}

TEST(MultTest, MultiplyTwoNegativeIntegers_1) {
    RegisterBlock rb;
    VariableMemory wm;
    Mult mult;

    rb.setRegister("AX", static_cast<int64_t>(-5));
    rb.setRegister("BX", static_cast<int64_t>(-10));

    std::string operand1 = "AX";
    std::string operand2 = "BX";
    mult.whatToDo(rb, wm, operand1, operand2);

    EXPECT_EQ(std::any_cast<int64_t>(rb.getRegister("AX")), 50);
}


TEST(MultTest, OverflowWhenMultiplyingDoubleAndLargeInteger_1) {
    RegisterBlock rb;
    VariableMemory wm;
    Mult mult;

    rb.setRegister("AX", static_cast<int64_t>(INT64_MAX));
    rb.setRegister("BX", static_cast<int64_t>(2));

    std::string operand1 = "AX";
    std::string operand2 = "BX";
    mult.whatToDo(rb, wm, operand1, operand2);

    EXPECT_EQ(std::any_cast<int64_t>(rb.getRegister("OF")), 1);
}


TEST(MultTest, MultiplyTwoLargeDoubles_1) {
    RegisterBlock rb;
    VariableMemory wm;
    Mult mult;

    rb.setRegister("AX", static_cast<double>(1.0e+150));
    rb.setRegister("BX", static_cast<double>(1.0e+150));

    std::string operand1 = "AX";
    std::string operand2 = "BX";
    mult.whatToDo(rb, wm, operand1, operand2);

    EXPECT_DOUBLE_EQ(std::any_cast<double>(rb.getRegister("AX")), 1.0e+300);
}

TEST(MultTest, MultiplyRegisterByItself_1) {
    RegisterBlock rb;
    VariableMemory wm;
    Mult mult;

    rb.setRegister("AX", static_cast<int64_t>(4));

    std::string operand1 = "AX";
    std::string operand2 = "AX";
    mult.whatToDo(rb, wm, operand1, operand2);

    EXPECT_EQ(std::any_cast<int64_t>(rb.getRegister("AX")), 16);
}

TEST(MultTest, MultiplyByZero_1) {
    RegisterBlock rb;
    VariableMemory wm;
    Mult mult;

    rb.setRegister("AX", static_cast<int64_t>(5));
    rb.setRegister("BX", static_cast<int64_t>(0));

    std::string operand1 = "AX";
    std::string operand2 = "BX";
    mult.whatToDo(rb, wm, operand1, operand2);

    EXPECT_EQ(std::any_cast<int64_t>(rb.getRegister("AX")), 0);
}


TEST(MultTest, MultiplyVariableByInteger) {
    RegisterBlock rb;
    VariableMemory wm;
    Mult mult;

    // Set up the variable in memory
    wm.setVariable("var1", static_cast<int64_t>(4)); // Variable in memory
    rb.setRegister("AX", static_cast<int64_t>(3));   // Register value

    std::string operand1 = "var1"; // Variable to multiply
    std::string operand2 = "AX";    // Register to multiply by
    mult.whatToDo(rb, wm, operand1, operand2);

    // Check if the variable is multiplied correctly
    EXPECT_EQ(std::any_cast<int64_t>(wm.getVariable("var1")), 12); // 4 * 3
}

TEST(MultTest, MultiplyVariableByDouble) {
    RegisterBlock rb;
    VariableMemory wm;
    Mult mult;

    // Set up the variable in memory
    wm.setVariable("var1", static_cast<int64_t>(5)); // Variable in memory
    rb.setRegister("AX", static_cast<double>(2.5));   // Register value

    std::string operand1 = "var1"; // Variable to multiply
    std::string operand2 = "AX";    // Register to multiply by
    mult.whatToDo(rb, wm, operand1, operand2);

    // Check if the variable is multiplied correctly
    EXPECT_DOUBLE_EQ(std::any_cast<double>(wm.getVariable("var1")), 12.5); // 5 * 2.5
}

TEST(MultTest, MultiplyVariableByIntegerWithOverflow) {
    RegisterBlock rb;
    VariableMemory wm;
    Mult mult;

    // Set up the variable in memory
    wm.setVariable("var1", static_cast<int64_t>(INT64_MAX)); // Variable in memory
    rb.setRegister("AX", static_cast<int64_t>(2));           // Register value

    std::string operand1 = "var1"; // Variable to multiply
    std::string operand2 = "AX";    // Register to multiply by
    mult.whatToDo(rb, wm, operand1, operand2);

    // Check for overflow handling
    EXPECT_EQ(std::any_cast<int64_t>(rb.getRegister("OF")), 1); // Overflow flag should be set
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}