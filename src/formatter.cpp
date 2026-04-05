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


#include "cmake-init/formatter.h"
#include "cmake-init/generation_context.h"
#include <sstream>

namespace cmake_init {

Formatter::Formatter(const GenerationContext& ctx) : ctx_(ctx) {}

std::string Formatter::format_cmake_version() const {
    std::stringstream ss;
    ss << "cmake_minimum_required(VERSION " << ctx_.cmake_version() << ")\n";
    return ss.str();
}

std::string Formatter::format_project() const {
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

std::string Formatter::format_options() const {
    std::stringstream ss;
    if (ctx_.enable_testing()) ss << "option(ENABLE_TESTS \"Enable tests\" OFF)\n";
    if (ctx_.enable_clang_tidy()) ss << "option(ENABLE_CLANG_TIDY \"Enable Clang-Tidy\" OFF)\n";
    if (ctx_.enable_cppcheck()) ss << "option(ENABLE_CPPCHECK \"Enable Cppcheck\" OFF)\n";
    return ss.str();
}

std::string Formatter::format_cxx_standard() const {
    std::stringstream ss;
    ss << "set(CMAKE_CXX_STANDARD " << ctx_.cxx_standard() << ")\n";
    ss << "set(CMAKE_CXX_STANDARD_REQUIRED ON)\n";
    ss << "set(CMAKE_CXX_EXTENSIONS OFF)\n";
    return ss.str();
}

std::string Formatter::format_c_standard() const {
    std::stringstream ss;
    ss << "set(CMAKE_C_STANDARD " << ctx_.c_standard() << ")\n";
    ss << "set(CMAKE_C_STANDARD_REQUIRED ON)\n";
    ss << "set(CMAKE_C_EXTENSIONS OFF)\n";
    return ss.str();
}

std::string Formatter::format_compile_commands() const {
    return "set(CMAKE_COMPILE_WARNING_AS_ERROR ON)\n";
}

std::string Formatter::format_bin() const {
    std::stringstream ss;
    ss << "add_subdirectory(src)\n";
    return ss.str();
}

std::string Formatter::format_dependencies() const {
    std::stringstream ss;
    ss << "# Dependencies (using FetchContent)\n";
    ss << "# FetchContent_Declare(\n";
    ss << "#     my_dependency\n";
    ss << "#     GIT_REPOSITORY https://github.com/example/repo\n";
    ss << "#     GIT_TAG main\n";
    ss << "# )\n";
    ss << "# FetchContent_MakeAvailable(my_dependency)\n";
    return ss.str();
}

std::string Formatter::format_src_cmake() const {
    std::stringstream ss;
    ss << "add_library(${TARGET} ${SRC})\n";
    ss << "target_include_directories(${TARGET} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)\n";
    ss << "target_link_libraries(${TARGET} PRIVATE ${LINK_LIBS})\n";
    return ss.str();
}

std::string Formatter::format_include_cmake() const {
    std::stringstream ss;
    ss << "target_include_directories(${TARGET} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})\n";
    return ss.str();
}

} // namespace cmake_init
