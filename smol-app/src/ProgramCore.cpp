#include "ProgramCore.h"

#include "debug_utils/Log.h"
#include "debug_utils/Profiler.h"
#include "Events/CoreEvents.h"
#include "Events/CustomEventHandler.h"
#include "Events/CW_CustomEvents.h"
#include "Renderer.h"

#include <imgui.h>
#include <imgui-sfml/imgui-SFML.h>

namespace CW {

	ProgramCore::ProgramCore()
	{
#ifdef CW_CUSTOM_EVENTS_LIST
		EventHandler::Get().Reserve(1024);
#endif
		m_Renderer = CreateUnique<Renderer>();
		CW_INFO("Core initialized.");
	}

	ProgramCore::~ProgramCore()
	{
		m_Renderer->ReleaseRenderTarget();
		ImGui::SFML::Shutdown();
		CW_INFO("Closing program.");
	}

	void ProgramCore::Run()
	{
		CW_INFO("Starting main loop.");
		CW_START_PROFILE_SESSION();
		CW_PROFILE_FUNCTION();
		sf::Clock deltaClock;

		while (m_App->IsRunning())
		{
			CW_PROFILE_SCOPE("main loop");

			sf::Time deltaTime = deltaClock.restart();

			PollEvents();
			PollUserEvents();

			ImGui::SFML::Update(m_App->GetRenderWindow(), deltaTime);

			if (!m_App->IsPaused())
			{
				m_App->Update(deltaTime.asSeconds());
				for (auto& layer : m_App->GetLayers())
				{
					if (layer->IsUpdateActive())
						layer->Update(deltaTime.asSeconds());
				}
			}
			else
			{
				m_App->PausedUpdate(deltaTime.asSeconds());
				for (auto& layer : m_App->GetLayers())
				{
					if (layer->IsUpdateActive())
						layer->PausedUpdate(deltaTime.asSeconds());
				}
			}

			auto& window = m_App->GetRenderWindow();
			window.clear(m_App->GetClearColor());
			m_Renderer->SetRenderTarget(&window);
			m_App->Draw(*m_Renderer);
			for (auto& layer : m_App->GetLayers())
			{
				if (layer->IsDrawActive())
					layer->Draw(*m_Renderer);
			}
			ImGui::SFML::Render(window);
			window.display();
		}
		CW_END_PROFILE_SESSION();
	}


	static void send_event_to_layers(Application& app, Event& event)
	{
		auto layerIter = app.GetLayers().rbegin();
		while (layerIter != app.GetLayers().rend())
		{
			auto& layer = *layerIter;
			if (event.Handled)
				return;
			if (layer->IsEventsActive())
				layer->OnEvent(event);
			++layerIter;
		}
	}

	template<class _EventType = void, class _SFMLEventType = void, class... _EventSubArgs>
	void dispatch_core_event(sf::Event& event, Application& app)
	{
		if (auto e = event.getIf<_SFMLEventType>())
		{
			_EventType dispached(*e);
			app.OnEvent(dispached);
			send_event_to_layers(app, dispached);
		}
		dispatch_core_event<_EventSubArgs...>(event, app);
	}

	template<>
	void dispatch_core_event<void, void>(sf::Event& event, Application& app)
	{
	}

	

	void ProgramCore::PollEvents()
	{
		CW_PROFILE_FUNCTION();
		while (std::optional event = m_App->GetRenderWindow().pollEvent())
		{
			{
				CW_PROFILE_SCOPE("ImGui events");
				ImGui::SFML::ProcessEvent(m_App->GetRenderWindow(), *event);
			}

			// особые случаи ивентов
			if (event->is<sf::Event::Closed>())
			{
				WindowClosed closed;
				m_App->OnEvent(closed);
				send_event_to_layers(*m_App, closed);
				OnClosed();
			}
			// ивенты MouseButtonPressed, MouseButtonReleased и MouseMoved отправляются, только если не были обработаны ImGui
			else if (auto e = event->getIf<sf::Event::MouseButtonPressed>(); e && !ImGui::GetIO().WantCaptureMouse)
			{
				MouseButtonPressed pressed(*e);
				m_App->OnEvent(pressed);
				send_event_to_layers(*m_App, pressed);
			}
			else if (auto e = event->getIf<sf::Event::MouseButtonReleased>(); e && !ImGui::GetIO().WantCaptureMouse)
			{
				MouseButtonReleased released(*e);
				m_App->OnEvent(released);
				send_event_to_layers(*m_App, released);
			}
			else if (auto e = event->getIf<sf::Event::MouseMoved>(); e && !ImGui::GetIO().WantCaptureMouse)
			{
				MouseMoved moved(*e);
				m_App->OnEvent(moved);
				send_event_to_layers(*m_App, moved);
			}
			else
			{
				CW_PROFILE_SCOPE("Dispacher function");
				dispatch_core_event<
					KeyPressed, sf::Event::KeyPressed,
					KeyReleased, sf::Event::KeyReleased,
					MouseWheelScrolled, sf::Event::MouseWheelScrolled,
					WindowResized, sf::Event::Resized
				>(*event, *m_App);
			}
		}
	}

#ifdef CW_CUSTOM_EVENTS_LIST
	template<class _EventType = void, class... _EventSubArgs>
	void dispatch_user_event(MyEvent& event, Application& app)
	{
		if (auto d = UserEventDispatcher<_EventType>(event))
		{
			d(app);
			return;
		}
		dispatch_user_event<_EventSubArgs...>(event, app);
	}

	template<>
	void dispatch_user_event<void>(MyEvent& event, Application& app)
	{
	}
#endif

	void ProgramCore::PollUserEvents()
	{
#ifdef CW_CUSTOM_EVENTS_LIST
		CW_PROFILE_FUNCTION();
		auto& events = EventHandler::Get().GetEvents();
		for (size_t i = 0; i < events.size(); ++i)
		{
			auto& event = events[i];
			dispatch_user_event<CW_CUSTOM_EVENTS_LIST>(event, *m_App);
		}
		EventHandler::Get().ClearEvents();
#endif
	}

	void ProgramCore::SetApplication(std::unique_ptr<Application>&& app)
	{
		m_App = std::forward<std::unique_ptr<Application>>(app);

		if (!ImGui::SFML::Init(m_App->GetRenderWindow()))
		{
			CW_CRITICAL("Failing initializing ImGui::SFML.");
		}
	}

	void ProgramCore::OnClosed()
	{
		m_App->Close();
	}

} // CW