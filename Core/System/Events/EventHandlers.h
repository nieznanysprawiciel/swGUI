#pragma once
/**
@file EventHandlers.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "DelegateContainer.h"



namespace sw {
namespace gui
{

struct IEventArgs;


/**@brief Container class for delegates.*/
class EventHandlers
{
	template< typename EventArgType > friend class EventProxy;
private:

	DelegatesContainerBaseOPtr		m_delegatesList;

public:
	explicit			EventHandlers();

	/**@brief Search for events container.
	@return This function can return nullptr if container haven't been created yet.*/
	DelegatesContainerBase*		FindContainer		( EventType eventID );

private:
	///@name Functions for EventProxy
	///@{

	/**@brief Adds delegates container.
	@return If container already existed, this function returns this container.*/
	DelegatesContainerBase*		AddContainer		( DelegatesContainerBaseOPtr&& container );

	/**@brief Removes container with deelgates.
	@return Returns false if container for eventID didn't exist.*/
	bool						RemoveContainer		( EventType eventID );

	/**@brief Sends event to visual tree using @ref RoutingStrategy specyfied in eventInfo.
	Calls @ref EventsSystem::RaiseEvent.
	@return Returns false if event couldn't be sent. False means you provided wrong argument type for this event,
	or sender type is different then registered. Normally you don't have to check this.*/
	bool						RaiseEvent			( const RegisteredEvent* eventInfo, UIElement* sender, IEventArgs* arguments );

	///@}
	
private:
	// Internal

	/**@brief Checks if container exists.*/
	bool						Exists				( EventType eventID );
};




}	// gui
}	// sw

