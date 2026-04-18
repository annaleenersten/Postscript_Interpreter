#pragma once
#include <variant>
#include <string>
#include <vector>
#include <functional>
#include <iostream>

class PSDict; 

struct CodeBlock {
    std::vector<std::string> code;
    PSDict* defining_env;
};

using Value = std::variant<
    bool,
    int,
    double,
    std::string,
    std::vector<std::string>,
    std::function<void()>,
    CodeBlock,
    PSDict*
>;

void print_value(const Value& v); 

