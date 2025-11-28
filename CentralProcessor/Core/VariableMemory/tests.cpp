#include "VariableMemory.h"
#include <gtest/gtest.h>
#include <stdexcept>

// Test setting and getting an int64_t variable
TEST(VariableMemoryTest, SetAndGetInt64Variable) {
    VariableMemory vm; // Create an instance of VariableMemory
    vm.setVariable("intVar", (int64_t)42);
    EXPECT_EQ(std::any_cast<int64_t>(vm.getVariable("intVar")), 42);

    // Update the variable
    vm.setVariable("intVar", (int64_t)100);
    EXPECT_EQ(std::any_cast<int64_t>(vm.getVariable("intVar")), 100);
}

// Test setting and getting a double variable
TEST(VariableMemoryTest, SetAndGetDoubleVariable) {
    VariableMemory vm; // Create an instance of VariableMemory
    vm.setVariable("doubleVar", 3.14);
    EXPECT_DOUBLE_EQ(std::any_cast<double>(vm.getVariable("doubleVar")), 3.14);

    // Update the variable
    vm.setVariable("doubleVar", 2.71);
    EXPECT_DOUBLE_EQ(std::any_cast<double>(vm.getVariable("doubleVar")), 2.71);
}

// Test getting a variable that does not exist
TEST(VariableMemoryTest, GetNonExistentVariable) {
    VariableMemory vm; // Create an instance of VariableMemory
    EXPECT_THROW(vm.getVariable("nonExistentVar"), std::out_of_range);
}

// Test setting a variable and then retrieving it as a different type
TEST(VariableMemoryTest, SetVariableAsDifferentType) {
    VariableMemory vm; // Create an instance of VariableMemory
    vm.setVariable("mixedVar", (int64_t)42);
    EXPECT_EQ(std::any_cast<int64_t>(vm.getVariable("mixedVar")), 42);

    // Set the same variable to a double
    vm.setVariable("mixedVar", 3.14);
    EXPECT_DOUBLE_EQ(std::any_cast<double>(vm.getVariable("mixedVar")), 3.14);
}

// Test that retrieving a variable as the wrong type throws an exception
TEST(VariableMemoryTest, GetVariableAsWrongType) {
    VariableMemory vm; // Create an instance of VariableMemory
    vm.setVariable("intVar", (int64_t)42);
    EXPECT_THROW(std::any_cast<double>(vm.getVariable("intVar")), std::bad_any_cast);
}

// Test setting and getting multiple variables
TEST(VariableMemoryTest, SetAndGetMultipleVariables) {
    VariableMemory vm; // Create an instance of VariableMemory
    vm.setVariable("var1", (int64_t)10);
    vm.setVariable("var2", 20.5);
    vm.setVariable("var3", (int64_t)30);

    EXPECT_EQ(std::any_cast<int64_t>(vm.getVariable("var1")), 10);
    EXPECT_DOUBLE_EQ(std::any_cast<double>(vm.getVariable("var2")), 20.5);
    EXPECT_EQ(std::any_cast<int64_t>(vm.getVariable("var3")), 30);
}

// Test overwriting a variable
TEST(VariableMemoryTest, OverwriteVariable) {
    VariableMemory vm; // Create an instance of VariableMemory
    vm.setVariable("var", (int64_t)50);
    EXPECT_EQ(std::any_cast<int64_t>(vm.getVariable("var")), 50);

    // Overwrite with a new value
    vm.setVariable("var", (int64_t)100);
    EXPECT_EQ(std::any_cast<int64_t>(vm.getVariable("var")), 100);
}

// Test retrieving a variable after multiple updates
TEST(VariableMemoryTest, RetrieveAfterMultipleUpdates) {
    VariableMemory vm; // Create an instance of VariableMemory
    vm.setVariable("updateVar", (int64_t)1);
    vm.setVariable("updateVar", (int64_t)2);
    vm.setVariable("updateVar", (int64_t)3);

    EXPECT_EQ(std::any_cast<int64_t>(vm.getVariable("updateVar")), 3);
}

// Test setting a variable to a negative double value
TEST(VariableMemoryTest, SetNegativeDoubleVariable) {
    VariableMemory vm; // Create an instance of VariableMemory
    vm.setVariable("negativeDouble", -3.14);
    EXPECT_DOUBLE_EQ(std::any_cast<double>(vm.getVariable("negativeDouble")), -3.14);
}

// Test setting a variable to zero
TEST(VariableMemoryTest, SetZeroVariable) {
    VariableMemory vm; // Create an instance of VariableMemory
    vm.setVariable("zeroInt", (int64_t)0);
    vm.setVariable("zeroDouble", 0.0);

    EXPECT_EQ(std::any_cast<int64_t>(vm.getVariable("zeroInt")), 0);
    EXPECT_DOUBLE_EQ(std::any_cast<double>(vm.getVariable("zeroDouble")), 0.0);
}

// Test that setting a variable to the same value does not change it
TEST(VariableMemoryTest, SetSameValue) {
    VariableMemory vm; // Create an instance of VariableMemory
    vm.setVariable("sameValue", (int64_t)42);
    EXPECT_EQ(std::any_cast<int64_t>(vm.getVariable("sameValue")), 42);

    // Set the same value again
    vm.setVariable("sameValue", (int64_t)42);
    EXPECT_EQ(std::any_cast<int64_t>(vm.getVariable("sameValue")), 42);
}

// Test that retrieving a variable as the wrong type throws an exception
TEST(VariableMemoryTest, GetVariableAsWrongTypeAfterUpdate) {
    VariableMemory vm; // Create an instance of VariableMemory
    vm.setVariable("intVar", (int64_t)42);
    EXPECT_THROW(std::any_cast<double>(vm.getVariable("intVar")), std::bad_any_cast);

    // Update to a double
    vm.setVariable("intVar", 3.14);
    EXPECT_NO_THROW(std::any_cast<double>(vm.getVariable("intVar")));
}

// Test that retrieving a variable that was never set throws an exception
TEST(VariableMemoryTest, GetNeverSetVariable) {
    VariableMemory vm; // Create an instance of VariableMemory
    EXPECT_THROW(vm.getVariable("neverSetVar"), std::out_of_range);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
