/**
@file EventsSystem.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "EventsSystem.h"

#include "swGUI/Core/Controls/UIElement.h"



namespace sw {
namespace gui
{


// ================================ //
// Allows to insert RegisteredEvent to map.
bool				operator<		( const RegisteredEvent& left, const RegisteredEvent& right )
{
	if( left.OwnerType < right.OwnerType )
		return true;
	else if( left.OwnerType == right.OwnerType )
	{
		if( left.EventArgumentsType < right.EventArgumentsType )
			return true;
		else if( left.EventArgumentsType == right.EventArgumentsType )
		{
			if( left.EventName < right.EventName )
				return true;
		}
	}

	return false;
}


// ================================ //
//
EventsSystem::EventsSystem()
	:	m_counter( 1 )
{}


// ================================ //
//
const RegisteredEvent*			EventsSystem::RegisterEvent		( const char* eventName, RoutingStrategy strategy, TypeID ownerType, TypeID eventTypeId )
{
	RegisteredEvent eventInfo( eventName, strategy, ownerType, eventTypeId );

	std::lock_guard< std::mutex > lock( m_registerMutex );
	
	eventInfo.ID = m_counter;

	// Note: if new entry have been added, we must increment m_counter. Otherwise event was already registered
	// and we use object stored in m_registeredEvents set.
	auto iter = m_registeredEvents.insert( eventInfo );
	if( iter.second )
		m_counter++;

	return &(*iter.first);
}

// ================================ //
//
bool				EventsSystem::RaiseEvent					( const RegisteredEvent* eventInfo, UIElement* sender, IEventArgsOPtr&& arguments )
{
	// Type checking. If sender is different then registered then something gone wrong.
	// Argument checking could be done only in debug mode...
	if( sender->GetType().is_derived_from( eventInfo->OwnerType ) )
		return false;

	if( !arguments->get_type().is_derived_from( eventInfo->EventArgumentsType ) )
		return false;

	switch( eventInfo->Strategy )
	{
		case RoutingStrategy::Direct:
			return RaiseDirectEvent( eventInfo, sender, arguments.get() );
		case RoutingStrategy::Bubble:
			return RaiseBubbleEvent( eventInfo, sender, arguments.get() );
		case RoutingStrategy::Tunnel:
			return RaiseTunnelEvent( eventInfo, sender, arguments.get() );
		default:
			return false;
	}
}

// ================================ //
//
bool				EventsSystem::RaiseDirectEvent				( const RegisteredEvent* eventInfo, UIElement* sender, IEventArgs* arguments )
{
	sender->InvokeEventDelegates( eventInfo->ID, sender, arguments, AccessKey() );
	return true;
}

// ================================ //
//
bool				EventsSystem::RaiseBubbleEvent				( const RegisteredEvent* eventInfo, UIElement* sender, IEventArgs* arguments )
{
	return false;
}

// ================================ //
//
bool				EventsSystem::RaiseTunnelEvent				( const RegisteredEvent* eventInfo, UIElement* sender, IEventArgs* arguments )
{
	return false;
}



// ================================ //
//
EventsSystem&		EventsSystem::Get()
{
	static EventsSystem manager;
	return manager;
}





}	// gui
}	// sw