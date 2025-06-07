#pragma once

#include "Event.h"

#define CW_BULD_EVENT_TYPE(type) EventType GetEventType() const { return EventType::type; } \
static EventType GetStaticEventType() { return EventType::type; }

/**
* 
* Custom events must be deriver from Event class defined in Event.h and defined inside CW namespace
* 
* Use CW_BUILD_EVENT_TYPE macro to add needed methods for it to work
* 
* After creating event type it must be listed on CW_CUSTOM_EVENTS_LIST macro in CW_EventConfig.h
* 
* Example:
* 
* class MessegeToUser
*	  : public Event
* {
* public:
* 	  std::string Messege;
* 
* 	  MessegeToUser(const char* messege) : Messege(messege) {}
* 	  CW_BULD_EVENT_TYPE(MessegeToUser)
* };
* 
*/

namespace CW {

	// Write your events here

} // CW