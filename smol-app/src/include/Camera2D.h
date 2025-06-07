#pragma once

#include "Events/Event.h"
#include "Events/CoreEvents.h"

#include <SFML/Graphics.hpp>

namespace CW {

	constexpr sf::Mouse::Button CAMERA_MOVE_BUTTON = sf::Mouse::Button::Right;

	class Camera2D
	{
	public:
		Camera2D(float x, float y, float width, float height);

		void OnEvent(Event& event);

		const sf::View& GetView() const;
		const float GetZoomFactor() const;

		sf::Vector2f PixelToWorldPosition(sf::Vector2i mousePos) const;
		
	private:
		bool OnMouseButtonPressed(MouseButtonPressed& e);
		bool OnMouseButtonReleased(MouseButtonReleased& e);
		bool OnMouseMoved(MouseMoved& e);
		bool OnMouseWheelScrolled(MouseWheelScrolled& e);
		bool OnResized(WindowResized& e);

	private:
		sf::View m_View;
		sf::Vector2i m_PrevPos;
		float m_ZoomFactor = 1.0f;
		bool m_IsMoving = false;
	};

} // CW