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


#ifndef GENERATIONCONTEXT_H
#define GENERATIONCONTEXT_H

#include "config.h"

enum class TargetType {
    Executable,
    Static_lib,
    Shared_lib
};

class GenerationContext {
public:
    explicit GenerationContext(const Config& config);

    std::string location() const;
    std::string project_name() const;
    std::string project_version() const;
    TargetType target_type() const;
    std::string cmake_version() const;
    std::string language() const;
    int cxx_standard() const;
    int c_standard() const;
    //std::string package_manager() const; TODO: Check package_maanger
    bool enable_testing() const;
    bool enable_clang_tidy() const;
    bool enable_cppcheck() const;

private:
    const Config& config_;
};

#endif // GENERATIONCONTEXT_H
