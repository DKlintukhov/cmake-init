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
#include "cmake-init/formatter.h"
#include "cmake-init/generation_context.h"
#include "cmake-init/config.h"

BOOST_AUTO_TEST_SUITE(CMakeListsFormatterTestSuite)

BOOST_AUTO_TEST_CASE(test_format_cmake_version) {
    cmake_init::Config config;
    config.set_answer("cmake_version", "3.28");
    cmake_init::GenerationContext ctx(config);
    cmake_init::Formatter formatter(ctx);

    std::string result = formatter.format_cmake_version();
    BOOST_CHECK(result.find("cmake_minimum_required(VERSION 3.28)") != std::string::npos);
}

BOOST_AUTO_TEST_CASE(test_format_project) {
    cmake_init::Config config;
    config.set_answer("project_name", "test_proj");
    config.set_answer("project_version", "1.2.3");
    config.set_answer("language", "CXX");
    cmake_init::GenerationContext ctx(config);
    cmake_init::Formatter formatter(ctx);

    std::string result = formatter.format_project();
    BOOST_CHECK(result.find("set(TARGET test_proj)") != std::string::npos);
    BOOST_CHECK(result.find("VERSION 1.2.3") != std::string::npos);
    BOOST_CHECK(result.find("LANGUAGES CXX") != std::string::npos);
}

BOOST_AUTO_TEST_CASE(test_format_options_enabled) {
    cmake_init::Config config;
    config.set_answer("enable_testing", "true");
    config.set_answer("enable_clang_tidy", "true");
    config.set_answer("enable_cppcheck", "true");
    cmake_init::GenerationContext ctx(config);
    cmake_init::Formatter formatter(ctx);

    std::string result = formatter.format_options();
    BOOST_CHECK(result.find("option(ENABLE_TESTS \"Enable tests\" OFF)") != std::string::npos);
    BOOST_CHECK(result.find("option(ENABLE_CLANG_TIDY \"Enable Clang-Tidy\" OFF)") != std::string::npos);
    BOOST_CHECK(result.find("option(ENABLE_CPPCHECK \"Enable Cppcheck\" OFF)") != std::string::npos);
}

BOOST_AUTO_TEST_CASE(test_format_options_disabled) {
    cmake_init::Config config;
    config.set_answer("enable_testing", "false");
    config.set_answer("enable_clang_tidy", "false");
    config.set_answer("enable_cppcheck", "false");
    cmake_init::GenerationContext ctx(config);
    cmake_init::Formatter formatter(ctx);

    std::string result = formatter.format_options();
    BOOST_CHECK(result.empty());
}

BOOST_AUTO_TEST_CASE(test_format_standards) {
    cmake_init::Config config;
    config.set_answer("cxx_standard", "20");
    config.set_answer("c_standard", "17");
    cmake_init::GenerationContext ctx(config);
    cmake_init::Formatter formatter(ctx);

    BOOST_CHECK(formatter.format_cxx_standard().find("set(CMAKE_CXX_STANDARD 20)") != std::string::npos);
    BOOST_CHECK(formatter.format_c_standard().find("set(CMAKE_C_STANDARD 17)") != std::string::npos);
}

BOOST_AUTO_TEST_CASE(test_format_bin) {
    cmake_init::Config config;
    cmake_init::GenerationContext ctx(config);
    cmake_init::Formatter formatter(ctx);

    std::string result = formatter.format_bin();
    BOOST_CHECK(result.find("add_library(${TARGET} ${SRC})") != std::string::npos);
    BOOST_CHECK(result.find("target_include_directories") != std::string::npos);
    BOOST_CHECK(result.find("add_subdirectory(src)") != std::string::npos);
}

BOOST_AUTO_TEST_CASE(test_format_src_cmake) {
    cmake_init::Config config;
    cmake_init::GenerationContext ctx(config);
    cmake_init::Formatter formatter(ctx);

    std::string result = formatter.format_src_cmake();
    BOOST_CHECK(result.find("add_library(${TARGET} ${SRC})") != std::string::npos);
    BOOST_CHECK(result.find("target_include_directories") != std::string::npos);
}

BOOST_AUTO_TEST_CASE(test_format_include_cmake) {
    cmake_init::Config config;
    cmake_init::GenerationContext ctx(config);
    cmake_init::Formatter formatter(ctx);

    std::string result = formatter.format_include_cmake();
    BOOST_CHECK(result.find("target_include_directories") != std::string::npos);
    BOOST_CHECK(result.find("INTERFACE") != std::string::npos);
}

BOOST_AUTO_TEST_SUITE_END()
