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


#include "cmake-init/config.h"
#include "cmake-init/prompter.h"
#include "cmake-init/generation_context.h"
#include "cmake-init/formatter.h"
#include <print>
#include <iostream>
#include <filesystem>

int main(int argc, const char** argv)
{
    const auto exe_filepath = std::filesystem::path(argv[0]);
    const auto config_filepath = exe_filepath.parent_path() / "config.json";

    auto config_result = cmake_init::Config::load_from_file(config_filepath);
    if (!config_result) {
        std::println(std::cerr, "Failed to load configuration from {}: {}", config_filepath.string(), config_result.error());
        return 1;
    }

    auto& config = *config_result;
    cmake_init::Prompter prompter;
    prompter.prompt_all(config);

    cmake_init::GenerationContext gen_context(config);
    cmake_init::Formatter formatter(gen_context);

    std::println("=== CMakeLists.txt ===");
    std::println("{}", formatter.format_cmake_version());
    std::println("{}", formatter.format_project());
    std::println("{}", formatter.format_options());
    std::println("{}", formatter.format_cxx_standard());
    std::println("{}", formatter.format_c_standard());
    std::println("{}", formatter.format_compile_commands());
    std::println("{}", formatter.format_dependencies());
    std::println("{}", formatter.format_bin());
    std::println("{}", formatter.format_src_cmake());
    std::println("{}", formatter.format_include_cmake());

    return 0;
}
