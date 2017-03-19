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

	///@}
	
private:
	// Internal

	/**@brief Checks if container exists.*/
	bool						Exists				( EventType eventID );
};




}	// gui
}	// sw

