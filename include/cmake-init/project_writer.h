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


#ifndef PROJECT_WRITER_H
#define PROJECT_WRITER_H

#include "cmake-init/generation_context.h"
#include <filesystem>
#include <string>
#include <expected>

namespace cmake_init {

class ProjectWriter {
public:
    explicit ProjectWriter(const GenerationContext& ctx);

    std::expected<void, std::string> write() const;

private:
    const GenerationContext& ctx_;

    std::filesystem::path project_path() const;
    void create_directories() const;
    void write_cmakeLists_txt() const;
    void write_src_cmake() const;
    void write_main_cpp() const;
    void write_header_h() const;
};

} // namespace cmake_init

#endif