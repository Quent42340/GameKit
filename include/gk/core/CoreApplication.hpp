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
#ifndef GK_COREAPPLICATION_HPP_
#define GK_COREAPPLICATION_HPP_

#include "gk/core/ApplicationStateStack.hpp"
#include "gk/core/ArgumentParser.hpp"
#include "gk/core/EventHandler.hpp"
#include "gk/core/GameClock.hpp"
#include "gk/core/Window.hpp"
#include "gk/resource/ResourceHandler.hpp"

namespace gk {

////////////////////////////////////////////////////////////
/// \brief Base class for your own Application
///
////////////////////////////////////////////////////////////
class CoreApplication {
	public:
		////////////////////////////////////////////////////////////
		/// \brief Constructor
		///
		/// \param argc Argument count
		/// \param argv Argument strings
		///
		////////////////////////////////////////////////////////////
		CoreApplication(int argc, char **argv);

		////////////////////////////////////////////////////////////
		/// \brief Run the application
		///
		/// \param isProtected Exceptions are catched if this parameter is set to `true` (default)
		///
		/// This function will run init(), then mainLoop().
		///
		////////////////////////////////////////////////////////////
		int run(bool isProtected = true);

	protected:
		////////////////////////////////////////////////////////////
		/// \brief Initialization function
		///
		/// This function is used to init engine and singletons.
		///
		////////////////////////////////////////////////////////////
		virtual void init();

		////////////////////////////////////////////////////////////
		/// \brief Create (or recreate) the window
		///
		/// If the window was already created, it closes it first.
		/// If \a style contains sf::Style::Fullscreen, then \a mode
		/// must be a valid video mode.
		///
		/// The fourth parameter is an optional structure specifying
		/// advanced OpenGL context settings such as antialiasing,
		/// depth-buffer bits, etc.
		///
		/// \param mode     Video mode to use (defines the width, height and depth of the rendering area of the window)
		/// \param title    Title of the window
		/// \param style    %Window style, a bitwise OR combination of sf::Style enumerators
		/// \param settings Additional settings for the underlying OpenGL context
		///
		////////////////////////////////////////////////////////////
		void createWindow(sf::VideoMode mode, const sf::String &title, sf::Uint32 style = sf::Style::Default, const sf::ContextSettings &settings = sf::ContextSettings());

		////////////////////////////////////////////////////////////
		/// \brief This function is called when a new window event is received
		///
		/// \param event Event received from SFML
		///
		/// This function is automatically called by handleEvents()
		///
		////////////////////////////////////////////////////////////
		virtual void onEvent(const sf::Event &) {}

		////////////////////////////////////////////////////////////
		/// \brief This function is called right before the program is closed
		///
		////////////////////////////////////////////////////////////
		virtual void onExit() {}

		////////////////////////////////////////////////////////////
		/// \brief Poll window events and send them to onEvent() and ApplicationStateStack
		///
		/// This function is automatically called by mainLoop()
		///
		////////////////////////////////////////////////////////////
		virtual void handleEvents();

		////////////////////////////////////////////////////////////
		/// \brief Game main loop, automatically called by run()
		///
		////////////////////////////////////////////////////////////
		virtual void mainLoop();

		////////////////////////////////////////////////////////////
		// Member data
		////////////////////////////////////////////////////////////
		ApplicationStateStack m_stateStack;                    ///< Stack containing application states

		GameClock m_clock;                                     ///< Simulated time system

		ResourceHandler m_resourceHandler;                     ///< Container for all game resources

		Window m_window;                                       ///< The main window

		RenderStates m_renderStates = RenderStates::Default;   ///< The default render states

		ArgumentParser m_argumentParser;                       ///< Helper for argument management

		EventHandler m_eventHandler;                           ///< Class responsible to store events and listeners
};

} // namespace gk

#endif // GK_COREAPPLICATION_HPP_

////////////////////////////////////////////////////////////
/// \class gk::CoreApplication
/// \ingroup core
///
/// This class provides an interface to create your own application.
///
/// You should add a class named `Application` that inherits from this class.
///
////////////////////////////////////////////////////////////
