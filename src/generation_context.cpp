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


#include "generation_context.h"

GenerationContext::GenerationContext(const Config& config) : config_(config) {}

std::string GenerationContext::project_name() const {
    return std::string(config_.get_answer("project_name", "my_project"));
}

std::string GenerationContext::project_version() const {
    return std::string(config_.get_answer("project_version", "0.1.0"));
}

std::string GenerationContext::target_type() const {
    return std::string(config_.get_answer("project_version", "Executable"));
}

std::string GenerationContext::cmake_version() const {
    return std::string(config_.get_answer("cmake_version", "3.25"));
}

std::string GenerationContext::language() const {
    return std::string(config_.get_answer("language", "C++"));
}

int GenerationContext::cxx_standard() const {
    return std::stoi(std::string(config_.get_answer("cxx_standard", "23")));
}

int GenerationContext::c_standard() const {
    return std::stoi(std::string(config_.get_answer("c_standard", "23")));
}

bool GenerationContext::enable_testing() const {
    return config_.get_answer("enable_testing", "false") == "true";
}

bool GenerationContext::enable_clang_tidy() const {
    return config_.get_answer("enable_clang_tidy", "false") == "true";
}

bool GenerationContext::enable_cppcheck() const {
    return config_.get_answer("enable_cppcheck", "false") == "true";
}
