#include "Application.h"

namespace CW {

	Application::Application(u32 width, u32 height, std::string_view title)
		: m_WindowTitle(title)
    {
		m_Window = CreateUnique<sf::RenderWindow>(sf::VideoMode({ width, height }), m_WindowTitle.c_str());
    }

	Application::~Application()
	{
		if (!m_Window->isOpen())
			m_Window->close();
	}

	std::vector<Unique<Layer>>& Application::GetLayers()
	{
		return m_Layers;
	}

	RenderWindow& Application::GetRenderWindow() const
	{
		return *m_Window;
	}

	Color Application::GetClearColor() const
	{
		return m_ClearColor;
	}

	bool Application::IsRunning() const
	{
		return m_Running;
	}

	void Application::Close()
	{
		m_Running = false;
	}

	bool Application::IsPaused() const
	{
		return m_Pause;
	}

	void Application::SwitchPause()
	{
		m_Pause = !m_Pause;
	}

	void Application::PopLayer()
	{
		m_Layers.pop_back();
	}

	void Application::EraseLayer(size_t index)
	{
		if (index >= m_Layers.size())
			CW_CRITICAL("Layer index out of bounds when erasing! \nindex = {}\nm_Layers.size() = {}", index, m_Layers.size());
		auto layer = m_Layers.erase(m_Layers.begin() + index);
		while (layer != m_Layers.end())
		{
			(*layer)->SetIndex(index);
			++index;
			++layer;
		}
	}

	void Application::EraseLayer(const Layer& layer)
	{
		size_t index = layer.GetIndex();
		EraseLayer(index);
	}

} // CW