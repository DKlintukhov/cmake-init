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


#ifndef CONFIG_H
#define CONFIG_H

#include <filesystem>
#include <string>
#include <string_view>
#include <vector>
#include <map>
#include <expected>

namespace cmake_init {

struct Question {
    std::string id;
    std::string prompt;
    std::string type;
    std::string default_val;
    std::vector<std::string> options;
};

class Config {
public:
    static std::expected<Config, std::string> load_from_file(const std::filesystem::path& filepath);

    const std::vector<Question>& questions() const;

    void set_answer(std::string id, std::string answer);

    std::string_view get_answer(std::string_view id, std::string_view default_val = "") const;

    const std::map<std::string, std::string>& all_answers() const;

private:
    std::vector<Question> questions_;
    std::map<std::string, std::string> answers_;
};

} // namespace cmake_init

#endif
