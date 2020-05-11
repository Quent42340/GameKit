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
#include "gk/core/input/KeyboardHandler.hpp"
#include "gk/core/Debug.hpp"
#include "gk/core/IntTypes.hpp"
#include "gk/core/XMLFile.hpp"

namespace gk {

void KeyboardHandler::loadKeysFromFile(const std::string &filename) {
	XMLFile doc(filename);

	tinyxml2::XMLElement *keys = doc.FirstChildElement("keys").ToElement();
	if (keys) {
		GameKey key = 0;
		tinyxml2::XMLElement *keyElement = keys->FirstChildElement("key");
		while (keyElement) {
			const char *keyName;
			if ((keyName = keyElement->Attribute("keycode")))
				m_keys[key] = KeyboardUtils::getKeyFromName(keyName);
			else
				gkWarning() << "Key '" << keyElement->Attribute("name") << "' is invalid";

			if(m_keys[key] == sf::Keyboard::Unknown) {
				gkWarning() << "Key '" << keyName << "' not recognized";
			}

			InputHandler::addKey(key);

			++key;
			keyElement = keyElement->NextSiblingElement("key");
		}
	}
}

bool KeyboardHandler::isKeyPressed(GameKey key) {
	return sf::Keyboard::isKeyPressed(m_keys[key]);
}

} // namespace gk

