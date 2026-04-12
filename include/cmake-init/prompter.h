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


#ifndef PROMPTER_H
#define PROMPTER_H

#include "cmake-init/config.h"
#include <iostream>
#include <string>

namespace cmake_init {

class Prompter {
public:
    explicit Prompter(std::istream& in = std::cin, std::ostream& out = std::cout);

    void prompt_all(Config& config);

private:
    std::istream& in_;
    std::ostream& out_;

    std::string prompt_string(const Question& q);
    std::string prompt_boolean(const Question& q);
    std::string prompt_choice(const Question& q);
};

} // namespace cmake_init

#endif
