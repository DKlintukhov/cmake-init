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
#include <format>

CMakeListsFormatter::CMakeListsFormatter(const GenerationContext& ctx) : ctx_(ctx) {}

std::string CMakeListsFormatter::format_cmake_version() const {
    return std::format("cmake_minimum_required(VERSION {})\n", ctx_.cmake_version());
}

std::string CMakeListsFormatter::format_project() const {
    return std::format(
        "project(\n"
        "    {}\n"
        "    VERSION {}\n"
        "    HOMEPAGE_URL \"{}\"\n"
        "    DESCRIPTION \"{}\"\n"
        "    LANGUAGES {}\n"
        ")\n",
        ctx_.project_name(),
        ctx_.project_version(),
        "homepage", // TODO: homepage
        "description", // TODO: description
        ctx_.language()
    );
}

std::string CMakeListsFormatter::format_cxx_standard() const {
    return std::format("set(CMAKE_CXX_STANDARD {})\n"
                       "set(CMAKE_CXX_STANDARD_REQUIRED ON)\n"
                       "set(CMAKE_CXX_EXTENSIONS OFF)\n",
                        ctx_.cxx_standard()
    );
}

std::string CMakeListsFormatter::format_c_standard() const {
    return std::format("set(CMAKE_C_STANDARD {})\n"
                       "set(CMAKE_C_STANDARD_REQUIRED ON)\n"
                       "set(CMAKE_C_EXTENSIONS OFF)\n",
                       ctx_.c_standard()
    );
}

std::string CMakeListsFormatter::format_compile_commands() const {
    return std::format("set(CMAKE_COMPILE_WARNING_AS_ERROR ON)\n");
}
