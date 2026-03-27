#pragma once

#include "config.h"
#include <iostream>
#include <string>

class Prompter {
public:
    explicit Prompter(std::istream& in = std::cin, std::ostream& out = std::cout);

    void prompt_all(Config& config);

private:
    std::istream& in_;
    std::ostream& out_;

    std::string prompt_string(const Question& q);
    std::string prompt_boolean(const Question& q);
    std::string prompt_choice(const Question& q);
};
