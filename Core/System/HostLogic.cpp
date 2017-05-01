#include "HostLogic.h"


#include "CommonTypes/CommonTypes.h"



// One pointer at least, but I don't know how much it needs in reality
#define STD_MAP_OVERHEAD_PER_ELEMENT 8


namespace sw {
namespace gui
{


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
{}

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
	size += m_focusPath.capacity() * sizeof( UIElement* );
	size += m_invalidated.capacity() * sizeof( UIElement* );
	size += m_controlTree.capacity() * sizeof( UIElement* );

	size += m_controlsNames.size() * ( sizeof( std::pair< UIElement*, std::string > ) + STD_MAP_OVERHEAD_PER_ELEMENT );

	//size += m_nativeWindow->MemorySize();

	for( auto control : m_controlTree )
		size += control->MemorySize();

	return size;
}

}	// gui
}	// sw
