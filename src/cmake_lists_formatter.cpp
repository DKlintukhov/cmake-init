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


#include "cmake_lists_formatter.h"
#include "generation_context.h"
#include <sstream>

CMakeListsFormatter::CMakeListsFormatter(const GenerationContext& ctx) : ctx_(ctx) {}

std::string CMakeListsFormatter::format_cmake_version() const {
    std::stringstream ss;
    ss << "cmake_minimum_required(VERSION " << ctx_.cmake_version() << ")\n";
    return ss.str();
}

std::string CMakeListsFormatter::format_project() const {
    std::stringstream ss;
    ss << "set(TARGET " << ctx_.project_name() << ")\n";
    ss << "project(\n";
    ss << "    ${TARGET}\n";
    ss << "    VERSION " << ctx_.project_version() << "\n";
    ss << "    HOMEPAGE_URL \"Project homepage\"\n";
    ss << "    DESCRIPTION \"Project description\"\n";
    ss << "    LANGUAGES " << ctx_.language() << "\n";
    ss << ")\n";
    ss << "if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)\n";
    ss << "    message(FATAL_ERROR \"In-source builds are not allowed. You should create separate directory for build files\")\n";
    ss << "endif()\n";
    return ss.str();
}

std::string CMakeListsFormatter::format_options() const {
    std::stringstream ss;
    if (ctx_.enable_testing()) ss << "option(ENABLE_TESTS \"Enable tests\" OFF)\n";
    if (ctx_.enable_clang_tidy()) ss << "option(ENABLE_CLANG_TIDY \"Enable Clang-Tidy\" OFF)\n";
    if (ctx_.enable_cppcheck()) ss << "option(ENABLE_CPPCHECK \"Enable Cppcheck\" OFF)\n";
    return ss.str();
}

std::string CMakeListsFormatter::format_cxx_standard() const {
    std::stringstream ss;
    ss << "set(CMAKE_CXX_STANDARD " << ctx_.cxx_standard() << ")\n";
    ss << "set(CMAKE_CXX_STANDARD_REQUIRED ON)\n";
    ss << "set(CMAKE_CXX_EXTENSIONS OFF)\n";
    return ss.str();
}

std::string CMakeListsFormatter::format_c_standard() const {
    std::stringstream ss;
    ss << "set(CMAKE_C_STANDARD " << ctx_.c_standard() << ")\n";
    ss << "set(CMAKE_C_STANDARD_REQUIRED ON)\n";
    ss << "set(CMAKE_C_EXTENSIONS OFF)\n";
    return ss.str();
}

std::string CMakeListsFormatter::format_compile_commands() const {
    return "set(CMAKE_COMPILE_WARNING_AS_ERROR ON)\n";
}

std::string CMakeListsFormatter::format_bin() const {
    switch (ctx_.target_type()) {
        case TargetType::Executable: return "add_executable(${TARGET} ${SRC})\n";
        case TargetType::Static_lib: return "add_library(${TARGET} static ${SRC})\n";
        default: return "add_library(${TARGET} ${SRC})\n";
    }
}
