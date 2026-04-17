#include "interpreter.h"
#include "operations.h"
#include <iostream>
#include <functional>
#include <stdexcept>

std::vector<Value> op_stack;
std::vector<PSDict> dict_stack;

void init_interpreter() {
    dict_stack.push_back(PSDict());
    auto& dictionary = dict_stack.back().dict;

    dictionary["exch"]   = std::function<void()>(exch_operation);
    dictionary["pop"]    = std::function<void()>(pop_operation);
    dictionary["copy"]   = std::function<void()>(copy_operation);
    dictionary["dup"]    = std::function<void()>(dup_operation);
    dictionary["clear"]  = std::function<void()>(clear_operation);
    dictionary["count"]  = std::function<void()>(count_operation);

    dictionary["add"]    = std::function<void()>(add_operation);
    dictionary["sub"]    = std::function<void()>(sub_operation);
    dictionary["mul"]    = std::function<void()>(mul_operation);
    dictionary["div"]    = std::function<void()>(div_operation);
    dictionary["idiv"]   = std::function<void()>(idiv_operation);
    dictionary["mod"]    = std::function<void()>(mod_operation);

    dictionary["abs"]    = std::function<void()>(abs_operation);
    dictionary["neg"]    = std::function<void()>(neg_operation);
    dictionary["ceiling"]= std::function<void()>(ceiling_operation);
    dictionary["floor"]  = std::function<void()>(floor_operation);
    dictionary["round"]  = std::function<void()>(round_operation);
    dictionary["sqrt"]   = std::function<void()>(sqrt_operation);

    dictionary["="]      = std::function<void()>(pop_print_operation);
    dictionary["def"]    = std::function<void()>(def_operation);

}


void lookup_in_dictionary(const std::string& input) {
    for (auto it = dict_stack.rbegin(); it != dict_stack.rend(); ++it) {

        try {
            Value value = it->get(input); 

            if (std::holds_alternative<std::function<void()>>(value)) {
                std::get<std::function<void()>>(value)();
            }
            else if (std::holds_alternative<std::vector<std::string>>(value)) {
                auto code = std::get<std::vector<std::string>>(value);
                for (const auto& token : code) {
                    process_input(token);
                }
            }
            else {
                op_stack.push_back(value);
            }

            return;
        }
        catch (const ParseFailed&) {
            continue;
        }
    }

    throw ParseFailed("Could not find " + input);
}

void process_input(const std::string& input) {
    // 1. Try parsing literal
    try {
        Value v = process_constants(input);
        op_stack.push_back(v);
        return;
    }
    catch (ParseFailed&) {
        // not a literal → continue
    }

    // 2. Try dictionary
    try{
        lookup_in_dictionary(input);
    }
    catch (const ParseFailed&) {
        // 3. If still not resolved → error point
        throw TypeMismatch("Undefined token: " + input);
    }

    
}
