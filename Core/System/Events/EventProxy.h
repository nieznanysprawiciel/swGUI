#pragma once
/**
@file EventProxy.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/



#include "DelegateContainer.h"
#include "EventHandlers.h"


namespace sw {
namespace gui
{


/**@brief Helper class for accessing event*/
template< typename EventArgType >
class EventProxy
{
public:
	typedef Delegate< EventArgType > DelegateType;
private:

	EventHandlers&							m_handlers;
	EventType								m_eventID;

public:
	explicit			EventProxy		( EventHandlers& delegatesContainer, EventType eventID );


	inline void			operator+=		( DelegateType delegate );
	inline bool			operator-=		( DelegateType delegate );
	inline void			AddDelegate		( DelegateType delegate );
	inline bool			RemoveDelegate	( DelegateType delegate );
};


//====================================================================================//
//			Implementation	
//====================================================================================//

// ================================ //
//
template< typename EventArgType >
inline					EventProxy< EventArgType >::EventProxy		( EventHandlers& delegatesContainer, EventType eventID )
	:	m_handlers( delegatesContainer )
	,	m_eventID( eventID )
{}

// ================================ //
//
template< typename EventArgType >
inline void				EventProxy< EventArgType >::operator+=		( typename EventProxy< EventArgType >::DelegateType delegate )
{
	AddDelegate( delegate );
}

// ================================ //
//
template< typename EventArgType >
inline bool				EventProxy< EventArgType >::operator-=		( typename EventProxy< EventArgType >::DelegateType delegate )
{
	return RemoveDelegate( delegate );
}

// ================================ //
//
template< typename EventArgType >
inline void				EventProxy< EventArgType >::AddDelegate		( typename EventProxy< EventArgType >::DelegateType delegate )
{
	// Find delegates container.
	DelegatesContainerBase* delegateContainer = m_handlers.FindContainer( m_eventID );
	DelegatesContainer< EventArgType >* typedDelegateContainer = nullptr;

	// Create delegates container if it doesn't exists.
	if( !delegateContainer )
	{
		DelegatesContainer< EventArgType >* container = new DelegatesContainer< EventArgType >( m_eventID );
		delegateContainer = m_handlers.AddContainer( std::move( DelegatesContainerBaseOPtr( container ) ) );
	}

	typedDelegateContainer = static_cast< DelegatesContainer< EventArgType >* >( delegateContainer );
	typedDelegateContainer->AddDelegate( delegate );
}

// ================================ //
//
template< typename EventArgType >
inline bool				EventProxy< EventArgType >::RemoveDelegate	( typename EventProxy< EventArgType >::DelegateType delegate )
{
	DelegatesContainerBase* delegateContainer = m_handlers.FindContainer( m_eventID );

	if( delegateContainer )
	{
		DelegatesContainer< EventArgType >* typedDelegateContainer = static_cast< DelegatesContainer< EventArgType >* >( delegateContainer );
		return typedDelegateContainer.RemoveDelegate( delegate );
	}
	return false;
}

}	// gui
}	// sw