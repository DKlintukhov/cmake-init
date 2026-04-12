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


#include "cmake-init/project_writer.h"
#include "cmake-init/formatter.h"
#include <fstream>

namespace cmake_init {

ProjectWriter::ProjectWriter(const GenerationContext& ctx, const std::filesystem::path& location)
    : ctx_(ctx), location_(location) {}

std::expected<void, std::string> ProjectWriter::write() const {
    try {
        create_directories();
        write_cmakeLists_txt();
        write_src_cmake();
        write_main_cpp();
        write_header_h();
        return {};
    } catch (const std::exception& e) {
        return std::unexpected(e.what());
    }
}

void ProjectWriter::create_directories() const {
    std::filesystem::create_directories(location_ / "src");
}

void ProjectWriter::write_cmakeLists_txt() const {
    std::ofstream out(location_ / "CMakeLists.txt");
    Formatter fmt(ctx_);
    out << fmt.format_cmake_version() << '\n';
    out << fmt.format_project() << '\n';
    out << fmt.format_options() << '\n';
    out << fmt.format_cxx_standard() << '\n';
    out << fmt.format_c_standard() << '\n';
    out << fmt.format_compile_commands() << '\n';
    out << fmt.format_dependencies() << '\n';
    out << fmt.format_bin() << '\n';
}

void ProjectWriter::write_src_cmake() const {
    std::ofstream out(location_ / "src" / "CMakeLists.txt");
    Formatter fmt(ctx_);
    out << fmt.format_src_cmake();
}

void ProjectWriter::write_main_cpp() const {
    auto main_path = location_ / "src" / "main.cpp";
    std::ofstream out(main_path);
    out << "int main(int argc, const char** argv) {\n";
    out << "    return 0;\n";
    out << "}\n";
}

void ProjectWriter::write_header_h() const {
    auto name = ctx_.project_name();
    std::string header_name = name + ".h";
    auto header_path = location_ / "include" / header_name;
    std::filesystem::create_directories(header_path.parent_path());

    std::ofstream out(header_path);
    out << "#ifndef " << name << "_H\n";
    out << "#define " << name << "_H\n\n";
    out << "namespace " << name << " {\n\n";
    out << "} // namespace " << name << "\n\n";
    out << "#endif\n";
}

} // namespace cmake_init
