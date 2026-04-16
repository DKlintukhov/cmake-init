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


#include <boost/test/unit_test.hpp>
#include <filesystem>
#include <ctime>
#include "cmake-init/config.h"
#include "cmake-init/generation_context.h"
#include "cmake-init/project_writer.h"

namespace fs = std::filesystem;

BOOST_AUTO_TEST_SUITE(LocationTests)

BOOST_AUTO_TEST_CASE(test_writer_creates_files_in_given_location) {
    // Prepare a unique temporary directory
    auto tmp_root = fs::temp_directory_path() / ("cmake-init-location-test-" + std::to_string(std::time(nullptr)));
    fs::remove_all(tmp_root);
    fs::create_directories(tmp_root);

    // Prepare config for context
    cmake_init::Config config;
    config.set_answer("project_name", "TestLocation");
    config.set_answer("project_version", "0.1.0");
    config.set_answer("language", "CXX");
    config.set_answer("cmake_version", "3.26");
    config.set_answer("cxx_standard", "20");
    config.set_answer("c_standard", "11");
    config.set_answer("enable_testing", "true");

    cmake_init::GenerationContext ctx(config);
    cmake_init::ProjectWriter writer(ctx, tmp_root);

    auto res = writer.write();
    BOOST_REQUIRE(res.has_value());

    // Check expected files exist
    BOOST_CHECK(fs::exists(tmp_root / "CMakeLists.txt"));
    BOOST_CHECK(fs::exists(tmp_root / "src" / "main.cpp"));
    BOOST_CHECK(fs::exists(tmp_root / "include" / "TestLocation.h"));

    // Cleanup
    fs::remove_all(tmp_root);
}

BOOST_AUTO_TEST_SUITE_END()
