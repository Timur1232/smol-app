#pragma once

#include "Application.h"
#include "Renderer.h"

namespace CW {

	class WindowResized;

	class ProgramCore
	{
	public:
		ProgramCore();
		ProgramCore(const ProgramCore&) = delete;
		ProgramCore(ProgramCore&&) = delete;

		~ProgramCore();

		// Основной цикл программы
		void Run();

		void SetApplication(std::unique_ptr<Application>&& app);

	private:
		void PollEvents();
		void PollUserEvents();

		void OnClosed();

	private:
		Unique<Application> m_App;
		Unique<Renderer> m_Renderer;
	};

} // CW