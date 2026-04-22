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

#include "cmake-init/config.h"
#include <boost/json/src.hpp>
#include <fstream>
#include <sstream>

namespace json = boost::json;

namespace cmake_init {

std::expected<Config, std::string> Config::load_from_file(const std::filesystem::path &filepath) {
  std::ifstream config_file(filepath);
  if (!config_file.is_open()) {
    return std::unexpected("Failed to open config file");
  }

  std::stringstream buffer;
  buffer << config_file.rdbuf();

  json::value jv;
  boost::system::error_code ec;
  jv = json::parse(buffer.str(), ec);
  if (ec) {
    return std::unexpected(std::string("Failed to parse config file: ") + ec.message());
  }

  auto &root = jv.as_object();
  if (!root.contains("questions") || !root.at("questions").is_array()) {
    return std::unexpected("The config file doesn't contain the required \"questions\" field");
  }

  Config config;
  for (const auto &q_val : root.at("questions").as_array()) {
    if (!q_val.is_object())
      continue;
    const auto &q = q_val.as_object();

    Question question;
    question.id = q.at("id").as_string().c_str();
    question.prompt = q.at("prompt").as_string().c_str();
    question.type = q.at("type").as_string().c_str();

    if (question.type == "boolean") {
      question.default_val = q.at("default").as_bool() ? "true" : "false";
    } else {
      question.default_val = q.at("default").as_string().c_str();
    }

    if (question.type == "choice" && q.contains("options") && q.at("options").is_array()) {
      for (const auto &opt : q.at("options").as_array()) {
        question.options.emplace_back(opt.as_string().c_str());
      }
    }

    config.questions_.push_back(std::move(question));
  }

  return config;
}

const std::vector<Question> &Config::questions() const { return questions_; }

void Config::set_answer(std::string id, std::string answer) {
  answers_.insert_or_assign(std::move(id), std::move(answer));
}

std::string_view Config::get_answer(std::string_view id, std::string_view default_val) const {
  auto it = answers_.find(id.data());
  if (it != answers_.end()) {
    return it->second;
  }
  return default_val;
}

const std::map<std::string, std::string> &Config::all_answers() const { return answers_; }

} // namespace cmake_init
