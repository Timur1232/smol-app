#include "EntryPoint.h"

#include <imgui.h>

#include "Application.h"
#include "SFML/Graphics.hpp"
#include "Types.h"
#include "Events/CoreEvents.h"
#include "utils/utils.h"

class MyApp
	: public CW::Application
{
public:
	MyApp()
		: Application(800, 600, "hello window"),
		m_SineRect({ { 0.0f, (float) m_Window->getSize().y / 2.0f }, {20.0f, 20.0f} }) {
	}
	~MyApp() = default;

	void Update(float deltaTime) override
	{
		m_Rect.position += m_Direction * m_Speed * deltaTime;
		if (m_Rect.position.x + m_Rect.size.x > m_Window->getSize().x
			|| m_Rect.position.x < 0.0f)
			m_Direction.x *= -1.0f;
		if (m_Rect.position.y + m_Rect.size.y > m_Window->getSize().y
			|| m_Rect.position.y < 0.0f)
			m_Direction.y *= -1.0f;
		UpdateImGui();
	}

	void PausedUpdate(float deltaTime) override
	{
		CW::Vec2f windowSize = (CW::Vec2f)m_Window->getSize();
		m_SineRect.position.x = CW::loop(m_SineRect.position.x, 0.0f, windowSize.x, m_Speed * deltaTime);
		m_SineRect.position.y = std::sin(m_SineRect.position.x / (sf::priv::pi * windowSize.x) * 60.0f) * 70.0f + windowSize.y / 2.0f;
		UpdateImGui();
	}

	void Draw(CW::Renderer& render) override
	{
		render.BeginRectangleShape()
			.Position(m_Rect.position)
			.Size(m_Rect.size)
			.Color(sf::Color::Red)
			.Draw();
		render.BeginRectangleShape()
			.Position(m_SineRect.position)
			.Size(m_SineRect.size)
			.Color(sf::Color::Cyan)
			.Draw()
			.SetDefault();
	}

	void OnEvent(CW::Event& event) override
	{
		CW::EventDispatcher dispatcher(event);

		dispatcher.Dispach<CW::WindowResized>(CW_BUILD_EVENT_FUNC(OnWindowsResize));
		dispatcher.Dispach<CW::KeyPressed>(CW_BUILD_EVENT_FUNC(OnKeyPressed));
	}

private:
	bool OnWindowsResize(CW::WindowResized& e)
	{
		m_Window->setView({ (CW::Vec2f) e.Size / 2.0f, (CW::Vec2f) e.Size });
		return false;
	}
	bool OnKeyPressed(CW::KeyPressed& e)
	{
		if (e.Data.code == sf::Keyboard::Key::Space)
			SwitchPause();
		return false;
	}
	void UpdateImGui()
	{
		ImGui::Begin("Test");
		ImGui::Text("Pause: %d", m_Pause);
		if (ImGui::Button("pause"))
			SwitchPause();
		ImGui::End();
	}

private:
	sf::FloatRect m_Rect{ {0.0f, 0.0f}, {40.0f, 40.0f} };
	sf::FloatRect m_SineRect;
	CW::Vec2f m_Direction{ 1.0f, 1.0f };
	float m_Speed = 200.0f;
};

std::unique_ptr<CW::Application> create_program(int argc, const char** argv)
{
	return std::make_unique<MyApp>();
}