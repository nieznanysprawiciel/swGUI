/**
@file HostLogic.coo
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "HostLogic.h"


#include "CommonTypes/CommonTypes.h"

#include "HostWindow.h"

// Events system.
#include "Events/EventsSystem.h"
#include "Events/EventsSystem.inl"

// Events arguments structures.
#include "Events/Input/KeyEventArgs.h"



// One pointer at least, but I don't know how much it needs in reality
#define STD_MAP_OVERHEAD_PER_ELEMENT 8


namespace sw {
namespace gui
{


// ================================ //
//
HostLogic::HostLogic	( HostWindow* hostWindow )
{
	m_mouseCapture = hostWindow;
	m_keyboardFocus.push_back( hostWindow );
}


// ================================ //
//
void					HostLogic::RemoveControl		( UIElement* control )
{}

// ================================ //
//
void					HostLogic::RegisterControlName	( UIElement* control, const std::string& name )
{
	assert( m_controlsNames.find( control ) == m_controlsNames.end() );
	m_controlsNames[ control ] = name;
}

// ================================ //
//
const std::string&		HostLogic::GetControlName	( UIElement* control )
{
	auto iter = m_controlsNames.find( control );
	if( iter != m_controlsNames.end() )
		return iter->second;
	else
		return EMPTY_STRING;
}

//====================================================================================//
//			GUI system interactions	
//====================================================================================//


// ================================ //
//
void			HostLogic::LostFocus		()
{}

// ================================ //
//
void			HostLogic::GotFocus			()
{}

// ================================ //
//
void			HostLogic::OnResized		( uint16 newWidth, uint16 newHeight )
{}

// ================================ //
//
void			HostLogic::OnMaximized		()
{}

// ================================ //
//
void			HostLogic::OnMinimized		()
{}


//====================================================================================//
//			Input handling	
//====================================================================================//


// ================================ //
//
void				HostLogic::HandleKeyInput			( const input::DeviceEvent& event, input::Device* device )
{
	// Send event to UIElement that has keyboard focus.
	if( m_keyboardFocus.size() )
	{
		UIElement* bottomElement = m_keyboardFocus.back();
		KeyEventArgsOPtr keyEvent = KeyEventArgsOPtr( new KeyEventArgs( static_cast< input::KeyboardDevice* >( device ), event.Key.Key ) );

		if( keyEvent->IsUp )
		{
			bool result = EventsSystem::Get().RaiseEvent( bottomElement->sPreviewKeyUp, bottomElement, keyEvent.get(), &UIElement::PreviewKeyUp );
			assert( result );		/// @todo Handle failing during event raising.

			if( !keyEvent->Handled )
			{
				result = EventsSystem::Get().RaiseEvent( bottomElement->sKeyUp, bottomElement, keyEvent.get(), &UIElement::KeyUp );
				assert( result );		/// @todo Handle failing during event raising.
			}
		}
		else
		{
			bool result = EventsSystem::Get().RaiseEvent( bottomElement->sPreviewKeyDown, bottomElement, keyEvent.get(), &UIElement::PreviewKeyDown );
			assert( result );		/// @todo Handle failing during event raising.

			if( !keyEvent->Handled )
			{
				result = EventsSystem::Get().RaiseEvent( bottomElement->sKeyDown, bottomElement, keyEvent.get(), &UIElement::KeyDown );
				assert( result );		/// @todo Handle failing during event raising.
			}
		}
		
	}
}

// ================================ //
//
void				HostLogic::HandleCharInput			( const input::DeviceEvent& event, input::Device* device )
{}

// ================================ //
//
void				HostLogic::HandleMouseButtonInput	( const input::DeviceEvent& event, input::Device* device )
{}

// ================================ //
//
void				HostLogic::HandleMouseWheelInput	( const input::DeviceEvent& event, input::Device* device )
{}

// ================================ //
//
void				HostLogic::HandleMouseMoveInput	( const input::DeviceEvent& event, input::Device* device )
{}


//====================================================================================//
//			Additional functionalities	
//====================================================================================//


// ================================ //
//
Size					HostLogic::GetMemorySize()
{
	Size size = sizeof( HostLogic );

	size += m_mousePath.capacity() * sizeof( UIElement* );
	size += m_invalidated.capacity() * sizeof( UIElement* );
	size += m_controlsTree.capacity() * sizeof( UIElement* );

	size += m_controlsNames.size() * ( sizeof( std::pair< UIElement*, std::string > ) + STD_MAP_OVERHEAD_PER_ELEMENT );

	//size += m_nativeWindow->MemorySize();

	for( auto control : m_controlsTree )
		size += control->MemorySize();

	return size;
}

}	// gui
}	// sw
