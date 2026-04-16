/*
 *  This file is part of cmake-init. See <https://github.com/DKlintukhov/cmake-init>.
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


#include "cmake-init/formatter.h"
#include "cmake-init/generation_context.h"

namespace cmake_init {

Formatter::Formatter(const GenerationContext& ctx) : ctx_(ctx) {}

std::string Formatter::format_cmake_version() const {
    return std::string("cmake_minimum_required(VERSION ") + ctx_.cmake_version() + ")\n";
}

std::string Formatter::format_project() const {
    return std::string("set(TARGET ") + ctx_.project_name() + ")\n"
        "project(\n"
        "    ${TARGET}\n"
        "    VERSION " + ctx_.project_version() + "\n"
        "    HOMEPAGE_URL \"Project homepage\"\n"
        "    DESCRIPTION \"Project description\"\n"
        "    LANGUAGES " + ctx_.language() + "\n"
        ")\n"
        "if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)\n"
        "    message(FATAL_ERROR \"In-source builds are not allowed. You should create separate directory for build files\")\n"
        "endif()\n";
}

std::string Formatter::format_options() const {
    std::string result;
    if (ctx_.enable_testing()) result += "option(ENABLE_TESTS \"Enable tests\" OFF)\n";
    if (ctx_.enable_clang_tidy()) result += "option(ENABLE_CLANG_TIDY \"Enable Clang-Tidy\" OFF)\n";
    if (ctx_.enable_cppcheck()) result += "option(ENABLE_CPPCHECK \"Enable Cppcheck\" OFF)\n";
    return result;
}

std::string Formatter::format_cxx_standard() const {
    return std::string("set(CMAKE_CXX_STANDARD ") + std::to_string(ctx_.cxx_standard()) + ")\n"
        "set(CMAKE_CXX_STANDARD_REQUIRED ON)\n"
        "set(CMAKE_CXX_EXTENSIONS OFF)\n";
}

std::string Formatter::format_c_standard() const {
    return std::string("set(CMAKE_C_STANDARD ") + std::to_string(ctx_.c_standard()) + ")\n"
        "set(CMAKE_C_STANDARD_REQUIRED ON)\n"
        "set(CMAKE_C_EXTENSIONS OFF)\n";
}

std::string Formatter::format_compile_commands() const {
    return "set(CMAKE_COMPILE_WARNING_AS_ERROR ON)\n";
}

std::string Formatter::format_bin() const {
    return "add_subdirectory(src)\n";
}

std::string Formatter::format_dependencies() const {
    return std::string("# Dependencies (using FetchContent)\n") +
        std::string("# FetchContent_Declare(\n") +
        std::string("#     my_dependency\n") +
        std::string("#     GIT_REPOSITORY https://github.com/example/repo\n") +
        std::string("#     GIT_TAG main\n") +
        std::string("# )\n") +
        std::string("# FetchContent_MakeAvailable(my_dependency)\n");
}

std::string Formatter::format_src_cmake() const {
    return std::string("add_library(${TARGET} ${SRC})\n") +
        std::string("target_include_directories(${TARGET} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)\n") +
        std::string("target_link_libraries(${TARGET} PRIVATE ${LINK_LIBS})\n");
}

std::string Formatter::format_include_cmake() const {
    return "target_include_directories(${TARGET} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})\n";
}

} // namespace cmake_init
