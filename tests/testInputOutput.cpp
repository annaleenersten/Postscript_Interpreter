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
//  Input/Output Operation Tests
// ================================================

class CaptureCout {
public:
    std::stringstream buffer;
    std::streambuf* old;

    CaptureCout() {
        old = std::cout.rdbuf(buffer.rdbuf());
    }

    ~CaptureCout() {
        std::cout.rdbuf(old);
    }

    std::string str() {
        return buffer.str();
    }
};

TEST(OutputOps, DoubleEqualsString) {
    reset();

    CaptureCout cap;

    process_input("(hello)");
    process_input("==");

    EXPECT_EQ(cap.str(), "(hello)\n");
}

TEST(OutputOps, DoubleEqualsNumber) {
    reset();

    CaptureCout cap;

    process_input("42");
    process_input("==");

    EXPECT_EQ(cap.str(), "42\n");
}

TEST(OutputOps, DoubleEqualsBoolean) {
    reset();

    CaptureCout cap;

    process_input("true");
    process_input("==");

    EXPECT_EQ(cap.str(), "true\n");
}

TEST(OutputOps, DoubleEqualsDict) {
    reset();

    CaptureCout cap;

    process_input("10");
    process_input("dict");
    process_input("==");

    EXPECT_EQ(cap.str(), "<<dict>>\n");
}

TEST(OutputOps, DoubleEqualsStringFormatting) {
    reset();

    CaptureCout cap;

    process_input("(world)");
    process_input("==");

    EXPECT_EQ(cap.str(), "(world)\n");
}

TEST(OutputOps, DoubleEqualsStackEmpty) {
    reset();

    CaptureCout cap;

    EXPECT_THROW(process_input("=="), TypeMismatch);
}