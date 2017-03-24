#pragma once
/**
@file RegisteredEvent.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swCommonLib/Common/TypesDefinitions.h"
#include "swCommonLib/Common/RTTR.h"


namespace sw {
namespace gui
{

typedef uint32 EventType;


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

// Implementation in EventsSystem.cpp
bool		operator<( const RegisteredEvent& left, const RegisteredEvent& right );


}	// gui
}	// sw