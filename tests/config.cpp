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


#define BOOST_TEST_MODULE ConfigTest
#include <boost/test/included/unit_test.hpp>
#include <fstream>
#include "config.h"

BOOST_AUTO_TEST_CASE(test_config_load) {
    // Create a temporary config file for testing
    std::string test_config = R"({
        "questions": [
            {
                "id": "project_name",
                "prompt": "Enter project name",
                "type": "string",
                "default": "my_project"
            }
        ]
    })";

    const auto config_file = std::filesystem::path("test_config.json");
    std::ofstream out(config_file);
    out << test_config;
    out.close();

    auto config_opt = Config::load_from_file(config_file);
    BOOST_REQUIRE(config_opt.has_value());

    auto& config = config_opt.value();
    BOOST_CHECK_EQUAL(config.questions().size(), 1);
    BOOST_CHECK_EQUAL(config.questions()[0].id, "project_name");
    
    // Test answering questions
    config.set_answer("project_name", "test_project");
    BOOST_CHECK_EQUAL(config.get_answer("project_name"), "test_project");
    
    // Test missing answer with default
    BOOST_CHECK_EQUAL(config.get_answer("missing", "default_val"), "default_val");

    std::filesystem::remove("test_config.json");
}

BOOST_AUTO_TEST_CASE(test_config_load_invalid) {
    auto config_opt = Config::load_from_file("nonexistent_file.json");
    BOOST_CHECK(!config_opt.has_value());
}
