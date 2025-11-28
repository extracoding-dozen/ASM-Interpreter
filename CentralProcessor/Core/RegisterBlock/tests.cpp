#include <gtest/gtest.h>
#include "RegisterBlock.h"

// Test setting and getting an integer register
TEST(RegisterBlockTest, SetAndGetIntRegister) {
    RegisterBlock rb;
    rb.setRegister("AX", (int64_t)42);
    EXPECT_EQ(std::any_cast<int64_t>(rb.getRegister("AX")), 42);
}

// Test setting and getting a double register
TEST(RegisterBlockTest, SetAndGetDoubleRegister) {
    RegisterBlock rb;
    rb.setRegister("BX", 3.14);
    EXPECT_DOUBLE_EQ(std::any_cast<double>(rb.getRegister("BX")), 3.14);
}

// Test setting an integer register and then a double register
TEST(RegisterBlockTest, SetIntThenDoubleRegister) {
    RegisterBlock rb;
    rb.setRegister("CX", (int64_t)100);
    EXPECT_EQ(std::any_cast<int64_t>(rb.getRegister("CX")), 100);

    rb.setRegister("CX", 2.71);
    EXPECT_DOUBLE_EQ(std::any_cast<double>(rb.getRegister("CX")), 2.71);
}

// Test getting a non-existent register
TEST(RegisterBlockTest, GetNonExistentRegister) {
    RegisterBlock rb;
    EXPECT_THROW(rb.getRegister("non_existent_reg"), std::out_of_range);
}

// Test setting and getting multiple registers
TEST(RegisterBlockTest, SetAndGetMultipleRegisters) {
    RegisterBlock rb;
    rb.setRegister("DX", (int64_t)10);
    rb.setRegister("SI", 20.5);
    rb.setRegister("DI", (int64_t)30);

    EXPECT_EQ(std::any_cast<int64_t>(rb.getRegister("DX")), 10);
    EXPECT_DOUBLE_EQ(std::any_cast<double>(rb.getRegister("SI")), 20.5);
    EXPECT_EQ(std::any_cast<int64_t>(rb.getRegister("DI")), 30);
}

// Test setting a register and then getting it as a different type
TEST(RegisterBlockTest, SetAndGetDifferentTypes) {
    RegisterBlock rb;
    rb.setRegister("SP", (int64_t)50);
    EXPECT_EQ(std::any_cast<int64_t>(rb.getRegister("SP")), 50);

    rb.setRegister("SP", 15.5);
    EXPECT_DOUBLE_EQ(std::any_cast<double>(rb.getRegister("SP")), 15.5);
}


// Test setting a register with a name that is not in the map
TEST(RegisterBlockTest, SetRegisterWithInvalidName) {
    RegisterBlock rb;
    EXPECT_THROW(rb.setRegister("INVALID_REG", (int64_t)100), std::out_of_range);
}

// Test getting a register value after setting it to a double
TEST(RegisterBlockTest, GetDoubleRegisterAfterSettingInt) {
    RegisterBlock rb;
    rb.setRegister("DX", static_cast<int64_t>(100)); // Set as int
    EXPECT_EQ(std::any_cast<int64_t>(rb.getRegister("DX")), 100); // Get as int

    rb.setRegister("DX", 3.14); // Set as double
    EXPECT_DOUBLE_EQ(std::any_cast<double>(rb.getRegister("DX")), 3.14); // Get as double
}

// Test setting multiple registers and checking their values
TEST(RegisterBlockTest, SetMultipleRegisters) {
    RegisterBlock rb;
    rb.setRegister("AX", static_cast<int64_t>(1));
    rb.setRegister("BX", static_cast<int64_t>(2));
    rb.setRegister("CX", 3.5);
    rb.setRegister("DX", 4.5);

    EXPECT_EQ(std::any_cast<int64_t>(rb.getRegister("AX")), 1);
    EXPECT_EQ(std::any_cast<int64_t>(rb.getRegister("BX")), 2);
    EXPECT_DOUBLE_EQ(std::any_cast<double>(rb.getRegister("CX")), 3.5);
    EXPECT_DOUBLE_EQ(std::any_cast<double>(rb.getRegister("DX")), 4.5);
}

// Test setting a register to zero
TEST(RegisterBlockTest, SetRegisterToZero) {
    RegisterBlock rb;
    rb.setRegister("AX", static_cast<int64_t>(0));
    EXPECT_EQ(std::any_cast<int64_t>(rb.getRegister("AX")), 0);

    rb.setRegister("BX", 0.0);
    EXPECT_DOUBLE_EQ(std::any_cast<double>(rb.getRegister("BX")), 0.0);
}

// Test setting a register and then resetting it
TEST(RegisterBlockTest, ResetRegister) {
    RegisterBlock rb;
    rb.setRegister("AX", static_cast<int64_t>(10));
    EXPECT_EQ(std::any_cast<int64_t>(rb.getRegister("AX")), 10);

    rb.setRegister("AX", static_cast<int64_t>(0)); // Reset to zero
    EXPECT_EQ(std::any_cast<int64_t>(rb.getRegister("AX")), 0);
}

// Test getting a register value after multiple sets
TEST(RegisterBlockTest, GetRegisterAfterMultipleSets) {
    RegisterBlock rb;
    rb.setRegister("AX", static_cast<int64_t>(10));
    rb.setRegister("AX", static_cast<int64_t>(20));
    EXPECT_EQ(std::any_cast<int64_t>(rb.getRegister("AX")), 20); // Should return the last set value

    rb.setRegister("BX", 1.5);
    rb.setRegister("BX", 2.5);
    EXPECT_DOUBLE_EQ(std::any_cast<double>(rb.getRegister("BX")), 2.5); // Should return the last set value
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

/*
int main() {
    RegisterBlock rb;
    rb.setRegister("AX", (int64_t)42);
    //rb.regNames.at("AX") += 200;
    std::any result = rb.getRegister("AX");
    try {
        double & res = std::any_cast<double &>(result);
        std::cout << res << std::endl;
    } catch(...){}
    try {
      int64_t & res = std::any_cast<int64_t &>(result);
      res += 30;
      result = rb.getRegister("AX");
      res = std::any_cast<int64_t &>(result);
      std::cout << res << std::endl;
      } catch(...){}
}
*/
