#pragma once

#include <concepts>
#include <vector>
#include <string>

#include "Types.h"
#include "Events/Event.h"
#include "Layer.h"
#include "debug_utils/Log.h"
#include "Renderer.h"

namespace CW {

	class Application
	{
	public:
		Application() = delete;
		Application(u32 width, u32 height, std::string_view title);
		virtual ~Application();

		virtual void Update(float deltaTime) = 0;
		virtual void Draw(Renderer& render) = 0;
		virtual void PausedUpdate(float deltaTime) {}
		virtual void OnEvent(Event& event) {}

		std::vector<Unique<Layer>>& GetLayers();

		RenderWindow& GetRenderWindow() const;
		Color GetClearColor() const;

		bool IsRunning() const;
		void Close();

		bool IsPaused() const;
		void SwitchPause();

		template <std::derived_from<Layer> T, class... Args>
		size_t PushLayer(Args&&... args)
		{
			size_t index = m_Layers.size();
			auto layer = m_Layers.emplace_back(CreateUnique<T>(std::forward<Args>(args)...));
			(*layer)->SetIndex(index);
			return index;
		}

		template <std::derived_from<Layer> T, class... Args>
		void InsertLayer(size_t index, Args&&... args)
		{
			if (index > m_Layers.size())
				CW_ASSERT("Layer index out of bounds when inserting! \nindex = {}\nm_Layers.size() = {}", index, m_Layers.size());
			auto layer = m_Layers.emplace(m_Layers.begin() + index, CreateUnique<T>(std::forward<Args>(args)...));
			(*layer)->SetIndex(index);
			++layer;
			++index;
			while (layer != m_Layers.end())
			{
				(*layer)->SetIndex(index);
				++layer;
				++index;
			}
		}

		void PopLayer();
		void EraseLayer(size_t index);
		void EraseLayer(const Layer& layer);

	protected:
		std::vector<Unique<Layer>> m_Layers;

		Unique<RenderWindow> m_Window;
		Color m_ClearColor{0, 0, 0, 0};
		std::string m_WindowTitle = "";

		bool m_Running = true;
		bool m_Pause = false;
	};

} // CW