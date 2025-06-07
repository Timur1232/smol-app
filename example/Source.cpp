#include "EntryPoint.h"
#include "Application.h"
#include "SFML/Graphics.hpp"
#include "Types.h"

class MyApp
	: public CW::Application
{
public:
	MyApp() : Application(800, 600, "hello window") {}
	~MyApp() = default;

	void Update(float deltaTime) override
	{
		m_Rect.position += m_Direction * m_Speed;
		if (m_Rect.getCenter().x + m_Rect.size.x / 2.0f > m_Window->getSize().x
			|| m_Rect.getCenter().x + m_Rect.size.x / 2.0f < 0.0f)
			m_Direction.x = -1.0f;
		if (m_Rect.getCenter().y + m_Rect.size.y / 2.0f > m_Window->getSize().y
			|| m_Rect.getCenter().y + m_Rect.size.y / 2.0f < 0.0f)
			m_Direction.y = -1.0f;
	}

	void Draw(CW::Renderer& render) override
	{
		render.BeginRectangleShape().DefaultAfterDraw()
			.Position(m_Rect.position)
			.Size(m_Rect.size)
			.Color(sf::Color::Red)
			.Draw();
	}

private:
	sf::FloatRect m_Rect{ {0.0f, 0.0f}, {20.0f, 20.0f} };
	CW::Vec2f m_Direction{1.0f, 1.0f};
	float m_Speed = 10.0f;
};

std::unique_ptr<CW::Application> create_programm(int, const char**)
{
	return std::make_unique<MyApp>();
}