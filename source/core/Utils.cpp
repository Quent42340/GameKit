/*
 * =====================================================================================
 *
 *  GameKit
 *
 *  Copyright (C) 2018-2020 Unarelith, Quentin Bazin <openminer@unarelith.net>
 *  Copyright (C) 2020 the GameKit contributors (see CONTRIBUTORS.md)
 *
 *  This file is part of GameKit.
 *
 *  GameKit is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  GameKit is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with GameKit; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA
 *
 * =====================================================================================
 */
#include <iomanip>
#include <sstream>

#include "gk/core/Utils.hpp"

namespace gk {

bool regexMatch(const std::string &str, const std::string &regex) {
	std::regex re(regex);
	std::cmatch m;

	return std::regex_match(str.c_str(), m, re);
}

std::string getCurrentTime(const char *format) {
	std::time_t t = std::time(nullptr);
	std::tm tm = *std::localtime(&t);

	std::stringstream sstream;
	sstream << std::put_time(&tm, format);

	return sstream.str();
}

} // namespace gk

