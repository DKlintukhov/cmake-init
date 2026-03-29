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


#include "config.h"
#include "prompter.h"
#include "generation_context.h"
#include <print>

int main(int args, const char** argv)
{
    const auto exe_filepath = std::filesystem::path(argv[0]);
    const auto config_filepath = exe_filepath.parent_path() / "config.json";
    
    auto config = Config::load_from_file(config_filepath);
    if (!config) {
        std::println(std::cerr, "Failed to load configuration from {}: {}", config_filepath.string(), config.error());
        return 1;
    }
    
    Prompter prompter;
    prompter.prompt_all(*config);

    GenerationContext gen_context(*config);
    
    return 0;
}
