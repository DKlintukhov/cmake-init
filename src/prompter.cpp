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


#include "cmake-init/prompter.h"
#include <algorithm>
#include <cctype>

namespace cmake_init {

Prompter::Prompter(std::istream& in, std::ostream& out) : in_(in), out_(out) {}

void Prompter::prompt_all(Config& config) {
    for (const auto& q : config.questions()) {
        std::string answer;
        if (q.type == "string") {
            answer = prompt_string(q);
        } else if (q.type == "boolean") {
            answer = prompt_boolean(q);
        } else if (q.type == "choice") {
            answer = prompt_choice(q);
        }
        config.set_answer(q.id, answer);
    }
}

std::string Prompter::prompt_string(const Question& q) {
    out_ << q.prompt << " [" << q.default_val << "]: ";
    std::string input;
    std::getline(in_, input);
    return input.empty() ? q.default_val : input;
}

std::string Prompter::prompt_boolean(const Question& q) {
    std::string def_label = (q.default_val == "true") ? "Y/n" : "y/N";
    out_ << q.prompt << " (" << def_label << "): ";

    std::string input;
    std::getline(in_, input);
    if (input.empty()) return q.default_val;

    std::transform(input.begin(), input.end(), input.begin(), [](unsigned char c){ return std::tolower(c); });
    if (input == "y" || input == "yes" || input == "true") return "true";
    if (input == "n" || input == "no" || input == "false") return "false";

    return q.default_val;
}

std::string Prompter::prompt_choice(const Question& q) {
    out_ << q.prompt << "\n";
    for (size_t i = 0; i < q.options.size(); ++i) {
        out_ << "  " << i + 1 << ". " << q.options[i] << "\n";
    }

    size_t default_idx = 0;
    for (size_t i = 0; i < q.options.size(); ++i) {
        if (q.options[i] == q.default_val) {
            default_idx = i + 1;
            break;
        }
    }

    out_ << "Enter choice [1-" << q.options.size() << ", default: " << default_idx << "]: ";

    std::string input;
    std::getline(in_, input);
    if (input.empty()) return q.default_val;

    try {
        int choice = std::stoi(input);
        if (choice >= 1 && static_cast<size_t>(choice) <= q.options.size()) {
            return q.options[choice - 1];
        }
    } catch (...) {
        // Fallback to searching by string name
        auto it = std::find(q.options.begin(), q.options.end(), input);
        if (it != q.options.end()) return *it;
    }

    return q.default_val;
}

} // namespace cmake_init
