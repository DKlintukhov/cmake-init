/*
 *  This file is part of cmake-init.
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
#include "cmake-init/generation_context.h"
#include "cmake-init/project_writer.h"
#include "cmake-init/prompter.h"
#include <filesystem>
#include <iostream>
#include <print>

int main(int argc, const char **argv) {
  const auto exe_filepath = std::filesystem::path(argv[0]);
  const auto location = argc > 1 ? std::filesystem::path(argv[1]) : std::filesystem::current_path();
  const auto config_filepath = exe_filepath.parent_path() / "config.json";

  auto config_result = cmake_init::Config::load_from_file(config_filepath);
  if (!config_result) {
    std::println(std::cerr, "Failed to load configuration from {}: {}", config_filepath.string(),
                 config_result.error());
    return 1;
  }

  auto &config = *config_result;
  cmake_init::Prompter prompter;
  prompter.prompt_all(config);

  cmake_init::GenerationContext gen_context(config);
  cmake_init::ProjectWriter writer(gen_context, location);

  auto result = writer.write();
  if (!result) {
    std::println(std::cerr, "Failed to create the project: {}", result.error());
    return 1;
  }

  std::println("The project created successfully!");

  return 0;
}