#pragma once
/**
@file EventsSystem.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swCommonLib/Common/TypesDefinitions.h"
#include "swCommonLib/Common/RTTR.h"

#include "EventProxy.h"
#include "EventHandlers.h"


#include <mutex>
#include <set>
#include <string>


namespace sw {
namespace gui
{




/**@brief Describes how event behaves in visual tree.*/
enum class RoutingStrategy : uint8
{
	Bubble,
	Direct,
	Tunnel
};



/**@brief Structure describes event registered by controls.

You can register event by calling @ref EventsSystem::RegisterEvent*/
struct RegisteredEvent
{
	TypeID				OwnerType;
	TypeID				EventArgumentsType;
	EventType			ID;
	RoutingStrategy		Strategy;
	std::string			EventName;

// ================================ //
//
	RegisteredEvent( const std::string& eventName, RoutingStrategy strategy, TypeID ownerType, TypeID eventTypeId )
		:	EventName( eventName )
		,	Strategy( strategy )
		,	OwnerType( ownerType )
		,	EventArgumentsType( eventTypeId )
	{}
};

bool		operator<( const RegisteredEvent& left, const RegisteredEvent& right );


/**@brief Events management.

For now this class stores only registered events. Think about future use.

Registering events needs to be in separate dll, otherwise controls can't register their static variables.*/
class EventsSystem
{
private:

	EventType						m_counter;

	std::mutex						m_registerMutex;
	std::set< RegisteredEvent >		m_registeredEvents;

protected:
public:
					~EventsSystem		() = default;

	/**@brief Registers new event and return idetifier used in DelegateContainers.*/
	const RegisteredEvent*		RegisterEvent		( const char* eventName, RoutingStrategy strategy, TypeID ownerType, TypeID eventTypeId );



public:
	static EventsSystem&		Get	();

private:
	explicit		EventsSystem		();
};


}	// gui
}	// sw
