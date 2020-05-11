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
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>

#include "gk/core/Mouse.hpp"

namespace gk {

Window *Mouse::s_window = nullptr;

Vector2i Mouse::s_lastMousePos{0, 0};
Vector2f Mouse::s_lastDelta{0, 0};

void Mouse::update(const sf::Event &event) {
	if (s_window) {
		Vector2i mousePos(event.mouseMove.x, event.mouseMove.y);

		const auto &windowSize = s_window->sf::Window::getSize();
		Vector2i windowCenter(windowSize.x / 2, windowSize.y / 2);

		if (s_lastMousePos.x != 0 && s_lastMousePos.y != 0)
			s_lastDelta = mousePos - s_lastMousePos;

		if (mousePos != windowCenter) {
			resetToWindowCenter();
			s_lastMousePos = windowCenter;
		}
		else {
			s_lastMousePos = mousePos;
		}
	}
}

void Mouse::resetToWindowCenter() {
	if (s_window) {
		sf::Vector2i windowCenter = {
			static_cast<int>(s_window->sf::Window::getSize().x / 2),
			static_cast<int>(s_window->sf::Window::getSize().y / 2)
		};

		sf::Mouse::setPosition(windowCenter, *s_window);
	}
}

void Mouse::setCursorGrabbed(bool isGrabbed) {
	if (s_window)
		s_window->setMouseCursorGrabbed(isGrabbed);
}

void Mouse::setCursorVisible(bool isVisible) {
	if (s_window)
		s_window->setMouseCursorVisible(isVisible);
}

Vector2i Mouse::getPosition() {
	if (s_window)
		return {sf::Mouse::getPosition(*s_window).x, sf::Mouse::getPosition(*s_window).y};
	return {sf::Mouse::getPosition().x, sf::Mouse::getPosition().y};
}

void Mouse::setPosition(const Vector2i &position) {
	if (s_window)
		sf::Mouse::setPosition({position.x, position.y}, *s_window);
	sf::Mouse::setPosition({position.x, position.y});
}

bool Mouse::isInRect(const IntRect &rect) {
	return rect.contains(getPosition());
}

} // namespace gk

