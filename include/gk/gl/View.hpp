/*
 * =====================================================================================
 *
 *       Filename:  View.hpp
 *
 *    Description:
 *
 *        Created:  01/01/2019 21:30:32
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef GK_VIEW_HPP
#define GK_VIEW_HPP

#include <gk/core/Rect.hpp>
#include <gk/core/Vector3.hpp>
#include <gk/gl/Transform.hpp>

namespace gk {

class View {
	public:
		View();
		View(const Vector3f &center, const Vector2f &size);
		explicit View(const FloatRect &rectangle);
		virtual ~View() = default;

		void setCenter(float x, float y, float z = 0);
		void setCenter(const Vector3f &position) { setCenter(position.x, position.y, position.y); }

		void setSize(float width, float height);
		void setSize(const Vector2f &size) { setSize(size.x, size.y); }

		void setRotation(float angle);

		void setViewport(const FloatRect &viewport) { m_viewport = viewport; }

		void reset(const FloatRect &rectangle);

		const Vector3f &getCenter() const { return m_position; }
		const Vector2f &getSize() const { return m_size; }

		float getRotation() const { return m_rotation; }

		const FloatRect &getViewport() const { return m_viewport; }

		void move(float offsetX, float offsetY, float offsetZ = 0);
		void move(const Vector3f &offset) { setCenter(m_position + offset); }

		void rotate(float angle) { setRotation(m_rotation + angle); }

		void zoom(float factor) { setSize(m_size.x * factor, m_size.y * factor); }

		virtual const Transform &getTransform() const;
		virtual const Transform &getViewTransform() const;

		virtual const Vector3f &getPosition() const { return m_position; }

	protected:
		mutable bool m_transformUpdated = false;
		mutable bool m_viewTransformUpdated = false;

		mutable Transform m_transform;
		mutable Transform m_viewTransform;

	private:
		Vector3f m_position;
		Vector2f m_size;

		float m_rotation = 0.0f;

		FloatRect m_viewport{0, 0, 1, 1};
};

} // namespace gk


#endif // GK_VIEW_HPP
