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


#include <boost/test/unit_test.hpp>
#include "config.h"
#include "generation_context.h"

BOOST_AUTO_TEST_SUITE(GenerationContextTestSuite)

BOOST_AUTO_TEST_CASE(test_generation_context_defaults) {
    Config config; // Empty answers
    GenerationContext ctx(config);

    BOOST_CHECK_EQUAL(ctx.project_name(), "my_project");
    BOOST_CHECK_EQUAL(ctx.project_version(), "0.1.0");
    BOOST_CHECK_EQUAL(ctx.enable_testing(), false);
}

BOOST_AUTO_TEST_CASE(test_generation_context_custom_values) {
    Config config;
    config.set_answer("project_name", "TestProject");
    config.set_answer("enable_testing", "true");

    GenerationContext ctx(config);

    BOOST_CHECK_EQUAL(ctx.project_name(), "TestProject");
    BOOST_CHECK_EQUAL(ctx.enable_testing(), true);
}

BOOST_AUTO_TEST_SUITE_END()