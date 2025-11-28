#include <gtest/gtest.h>
#include "Mov.h"
#include "../../RegisterBlock/RegisterBlock.h"
#include "../../VariableMemory/VariableMemory.h"


TEST(MovTest, MoveIntegerFromRegisterToRegister) {
    RegisterBlock rb;
    VariableMemory wm;
    Mov mov;

    rb.setRegister("AX", static_cast<int64_t>(10));
    std::string operand1 = "BX";
    std::string operand2 = "AX";
    mov.whatToDo(rb, wm, operand1, operand2);

    EXPECT_EQ(std::any_cast<int64_t>(rb.getRegister("BX")), 10);
}

TEST(MovTest, MoveDoubleFromRegisterToRegister) {
    RegisterBlock rb;
    VariableMemory wm;
    Mov mov;

    rb.setRegister("AX", static_cast<double>(3.14));
    std::string operand1 = "BX";
    std::string operand2 = "AX";
    mov.whatToDo(rb, wm, operand1, operand2);

    EXPECT_DOUBLE_EQ(std::any_cast<double>(rb.getRegister("BX")), 3.14);
}

TEST(MovTest, MoveIntegerFromVariableToRegister) {
    RegisterBlock rb;
    VariableMemory wm;
    Mov mov;

    wm.setVariable("var1", static_cast<int64_t>(42));
    std::string operand1 = "AX";
    std::string operand2 = "var1";
    mov.whatToDo(rb, wm, operand1, operand2);

    EXPECT_EQ(std::any_cast<int64_t>(rb.getRegister("AX")), 42);
}

TEST(MovTest, MoveDoubleFromVariableToRegister) {
    RegisterBlock rb;
    VariableMemory wm;
    Mov mov;

    wm.setVariable("var1", static_cast<double>(2.718));
    std::string operand1 = "AX";
    std::string operand2 = "var1";
    mov.whatToDo(rb, wm, operand1, operand2);

    EXPECT_DOUBLE_EQ(std::any_cast<double>(rb.getRegister("AX")), 2.718);
}

TEST(MovTest, MoveIntegerFromRegisterToVariable) {
    RegisterBlock rb;
    VariableMemory wm;
    Mov mov;
    wm.setVariable("var1", 0.0);
    rb.setRegister("AX", static_cast<int64_t>(100));
    std::string operand1 = "var1";
    std::string operand2 = "AX";
    mov.whatToDo(rb, wm, operand1, operand2);

    EXPECT_EQ(std::any_cast<int64_t>(wm.getVariable("var1")), 100);
}

TEST(MovTest, MoveDoubleFromRegisterToVariable) {
    RegisterBlock rb;
    VariableMemory wm;
    Mov mov;
    wm.setVariable("var1", 0.0);
    rb.setRegister("AX", static_cast<double>(1.618));
    std::string operand1 = "var1";
    std::string operand2 = "AX";
    mov.whatToDo(rb, wm, operand1, operand2);

    EXPECT_DOUBLE_EQ(std::any_cast<double>(wm.getVariable("var1")), 1.618);
}

TEST(MovTest, MoveIntegerFromStringToRegister) {
    RegisterBlock rb;
    VariableMemory wm;
    Mov mov;

    std::string operand1 = "AX";
    std::string operand2 = "123";
    mov.whatToDo(rb, wm, operand1, operand2);

    EXPECT_EQ(std::any_cast<int64_t>(rb.getRegister("AX")), 123);
}

TEST(MovTest, MoveDoubleFromStringToRegister) {
    RegisterBlock rb;
    VariableMemory wm;
    Mov mov;

    std::string operand1 = "AX";
    std::string operand2 = "3.14159";
    mov.whatToDo(rb, wm, operand1, operand2);

    EXPECT_DOUBLE_EQ(std::any_cast<double>(rb.getRegister("AX")), 3.14159);
}

TEST(MovTest, MoveStringToVariable) {
    RegisterBlock rb;
    VariableMemory wm;
    Mov mov;
    wm.setVariable("var1", 0.0);
    std::string operand1 = "var1";
    std::string operand2 = "456";
    mov.whatToDo(rb, wm, operand1, operand2);

    EXPECT_EQ(std::any_cast<int64_t>(wm.getVariable("var1")), 456);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}