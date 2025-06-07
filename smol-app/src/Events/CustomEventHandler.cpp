#include "Events/CustomEventHandler.h"

#ifdef CW_CUSTOM_EVENTS_LIST
namespace CW {

	EventHandler& EventHandler::Get()
	{
		static EventHandler handler;
		return handler;
	}

	void EventHandler::Reserve(size_t eventReserve)
	{
		m_UserEvents.reserve(eventReserve);
	}

} // CW
#endif