/*
 * =====================================================================================
 *
 *       Filename:  TextInput.hpp
 *
 *    Description:
 *
 *        Created:  22/01/2018 14:35:10
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef GK_TEXTINPUT_HPP_
#define GK_TEXTINPUT_HPP_

#include "gk/core/SDLHeaders.hpp"
#include "gk/graphics/RectangleShape.hpp"
#include "gk/graphics/Text.hpp"

namespace gk {

class TextInput : public Drawable, public Transformable {
	public:
		TextInput();

		void onEvent(const SDL_Event &event);

		const std::string &content() const { return m_content; }

		Vector2f getSize() const { return m_rectText.getSize(); }

		void setPosition(float x, float y);
		void setSize(u16 width, u16 height);
		void setCharacterLimit(u16 characterLimit) { m_characterLimit = characterLimit; }
		void setContent(const std::string &content) { m_content = content; m_text.setString(m_content + m_cursor); }
		void setKeyboardSound(const std::string &keyboardSound) { m_keyboardSound = keyboardSound; }
		void setCursor(const std::string &cursor) { m_cursor = cursor; m_text.setString(m_content + m_cursor); }

	private:
		void draw(RenderTarget &target, RenderStates states) const override;

		RectangleShape m_rectText;

		Text m_text;
		std::string m_content;

		u16 m_characterLimit = 0;

		std::string m_keyboardSound;

		std::string m_cursor = "|";
};

} // namespace gk

#endif // GK_TEXTINPUT_HPP_