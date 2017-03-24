/**
@file UIElement.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "UIElement.h"


namespace sw {
namespace gui
{






// ================================ //
//
void		UIElement::InvokeEventDelegates		( EventType eventID, UIElement* sender, IEventArgs* e, AccessKey )
{
	auto container = m_eventHandlers.FindContainer( eventID );
	if( container )
		container->CallDelegates( sender, e );
}

}	// gui
}	// sw

