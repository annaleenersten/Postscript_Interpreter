#include <gtest/gtest.h>
#include <sstream>
#include <iostream>
#include "parser.h"
#include "interpreter.h"

extern void process_input(const std::string& input);
extern std::vector<Value> op_stack;
extern std::vector<PSDict*> dict_stack;

extern void reset();

// ================================================
//  Flow Control Operation Tests
// ================================================

TEST(ControlFlow, IfTrueExecutesBlock) {
    reset();

    process_input("true");
    process_input("{ 10 }");
    process_input("if");

    ASSERT_FALSE(op_stack.empty());
    EXPECT_EQ(std::get<int>(op_stack.back()), 10);
}

TEST(ControlFlow, IfFalseSkipsBlock) {
    reset();

    process_input("false");
    process_input("{ 10 }");
    process_input("if");

    EXPECT_TRUE(op_stack.empty());
}

TEST(ControlFlow, IfElseTruePath) {
    reset();

    process_input("true");
    process_input("{ 1 }");
    process_input("{ 2 }");
    process_input("ifelse");

    EXPECT_EQ(std::get<int>(op_stack.back()), 1);
}

TEST(ControlFlow, IfElseFalsePath) {
    reset();

    process_input("false");
    process_input("{ 1 }");
    process_input("{ 2 }");
    process_input("ifelse");

    ASSERT_FALSE(op_stack.empty());
    EXPECT_EQ(std::get<int>(op_stack.back()), 2);
}

TEST(ControlFlow, RepeatExecutesMultipleTimes) {
    reset();

    process_input("3");
    process_input("{ 5 }");
    process_input("repeat");

    ASSERT_EQ(op_stack.size(), 3);
    for (auto& v : op_stack) {
        EXPECT_EQ(std::get<int>(v), 5);
    }
}

TEST(ControlFlow, RepeatZeroTimes) {
    reset();

    process_input("0");
    process_input("{ 5 }");
    process_input("repeat");

    EXPECT_TRUE(op_stack.empty());
}

TEST(ControlFlow, ForBasicLoop) {
    reset();

    process_input("1");
    process_input("1");
    process_input("3");
    process_input("{ dup }");
    process_input("for");

    ASSERT_EQ(op_stack.size(), 6);

    EXPECT_EQ(std::get<int>(op_stack[0]), 1);
    EXPECT_EQ(std::get<int>(op_stack[1]), 1);
    EXPECT_EQ(std::get<int>(op_stack[2]), 2);
    EXPECT_EQ(std::get<int>(op_stack[3]), 2);
    EXPECT_EQ(std::get<int>(op_stack[4]), 3);
    EXPECT_EQ(std::get<int>(op_stack[5]), 3);
}

TEST(ControlFlow, IfExecutesExpression) {
    reset();

    process_input("true");
    process_input("{ 2 3 add }");
    process_input("if");

    ASSERT_FALSE(op_stack.empty());
    EXPECT_EQ(std::get<int>(op_stack.back()), 5);
}