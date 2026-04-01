/*
 *  This file is part of nzbget. See <https://github.com/DKlintukhov/cmake-init>.
 *
 *  Copyright (C) 2026 Denis <denis.klintukhov@gmail.com>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see <https://www.gnu.org/licenses/>.
 */


#include "prompter.h"
#include <algorithm>
#include <cctype>

Prompter::Prompter(std::istream& in, std::ostream& out) : in_(in), out_(out) {}

void Prompter::prompt_all(Config& config) {
    bool ok = false;
    while (!ok) {
        for (const auto& q : config.questions()) {
            std::string answer;
            if (q.type == "string") {
                answer = prompt_string(q);
            } else if (q.type == "boolean") {
                answer = prompt_boolean(q);
            } else if (q.type == "choice") {
                answer = prompt_choice(q);
            } else {
                answer = prompt_string(q);
            }
            config.set_answer(q.id, std::move(answer));
        }
        
        // Find max prompt length for padding
        size_t max_len = 0;
        for (const auto& q : config.questions()) {
            if (q.prompt.length() > max_len) {
                max_len = q.prompt.length();
            }
        }

        for (const auto& q : config.questions()) {
            std::string answer = std::string(config.get_answer(q.id));
            if (q.type == "boolean") {
                answer = (answer == "true" || answer == "1") ? "yes" : "no";
            }
            
            std::string padding(max_len - q.prompt.length(), ' ');
            out_ << q.prompt << padding << " : " << answer << "\n";
        }
        
        for (;;) {
            out_ << "OK? (yes/no) [yes]: ";
            std::string input;
            std::getline(in_, input);

            auto start = input.find_first_not_of(" \t\r\n");
            if (start != std::string::npos) {
                auto end = input.find_last_not_of(" \t\r\n");
                input = input.substr(start, end - start + 1);
            }

            std::transform(input.begin(), input.end(), input.begin(),
                           [](unsigned char c){ return std::tolower(c); });

            if (input.empty() || input == "yes" || input == "y") {
                ok = true;
                break;
            } else if (input == "no" || input == "n") {
                out_ << "\nRestarting configuration...\n\n";
                break;
            }
        }
    }
    
    out_ << "cmake-init: INFO: Successfully initialized configuration.\n";
}

std::string Prompter::prompt_string(const Question& q) {
    std::string input;
    out_ << q.prompt << " [" << q.default_val << "]: ";
    std::getline(in_, input);

    auto start = input.find_first_not_of(" \t\r\n");
    if (start != std::string::npos) {
        auto end = input.find_last_not_of(" \t\r\n");
        input = input.substr(start, end - start + 1);
    } else {
        input = "";
    }

    if (input.empty()) {
        return q.default_val;
    }
    return input;
}

std::string Prompter::prompt_boolean(const Question& q) {
    while (true) {
        std::string default_str = (q.default_val == "true" || q.default_val == "1") ? "yes" : "no";
        
        std::string p = q.prompt;
        if (!p.empty() && p.back() == '?') {
            p.pop_back();
        }
        
        out_ << p << "? [" << default_str << "]: ";
        
        std::string input;
        std::getline(in_, input);

        auto start = input.find_first_not_of(" \t\r\n");
        if (start != std::string::npos) {
            auto end = input.find_last_not_of(" \t\r\n");
            input = input.substr(start, end - start + 1);
        } else {
            input = "";
        }

        if (input.empty()) {
            return q.default_val;
        }

        std::string lower_input = input;
        std::transform(lower_input.begin(), lower_input.end(), lower_input.begin(),
                       [](unsigned char c){ return std::tolower(c); });

        if (lower_input == "y" || lower_input == "yes" || lower_input == "true" || lower_input == "1") {
            return "true";
        } else if (lower_input == "n" || lower_input == "no" || lower_input == "false" || lower_input == "0") {
            return "false";
        }

        out_ << "Invalid input. Please enter 'yes' or 'no'.\n";
    }
}

std::string Prompter::prompt_choice(const Question& q) {
    if (q.options.empty()) {
        return prompt_string(q);
    }

    while (true) {
        out_ << q.prompt << " (";
        for (size_t i = 0; i < q.options.size(); ++i) {
            out_ << q.options[i];
            if (i < q.options.size() - 1) {
                out_ << "|";
            }
        }
        out_ << ") [" << q.default_val << "]: ";

        std::string input;
        std::getline(in_, input);

        auto start = input.find_first_not_of(" \t\r\n");
        if (start != std::string::npos) {
            auto end = input.find_last_not_of(" \t\r\n");
            input = input.substr(start, end - start + 1);
        } else {
            input = "";
        }

        if (input.empty()) {
            return q.default_val;
        }

        std::string lower_input = input;
        std::transform(lower_input.begin(), lower_input.end(), lower_input.begin(),
                       [](unsigned char c){ return std::tolower(c); });
        
        for (const auto& opt : q.options) {
            std::string lower_opt = opt;
            std::transform(lower_opt.begin(), lower_opt.end(), lower_opt.begin(),
                           [](unsigned char c){ return std::tolower(c); });
            if (lower_input == lower_opt) {
                return opt;
            }
        }

        out_ << "Invalid selection. Please enter one of the options.\n";
    }
}
