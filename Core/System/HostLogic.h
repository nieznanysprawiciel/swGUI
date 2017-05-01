#pragma once
/**
@file HostLogic.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGUI/Core/Controls/UIElement.h"

#include <vector>
#include <map>



namespace sw {
namespace gui
{




/**@brief Logic of host window for managing child controls.

@ingroup ControlsFramework*/
class HostLogic
{
private:

	std::vector< UIElement* >	m_mousePath;		///< Controls hierarchy that captured mouse in this frame.
	std::vector< UIElement* >	m_focusPath;		///< Controls hierarchy that have focus in this frame.
	std::vector< UIElement* >	m_invalidated;		///< Controls which needs to be redrawn in this frame.

	std::vector< UIElement* >	m_controlTree;		///< Top level controls.

	///@name Controls info
	///@{

	/// Map containing windows names. Most controls don't have name, so it's better to store
	/// them separatly, to lower memory consumption.
	std::map< UIElement*, std::string >		m_controlsNames;

	///@}

protected:
public:
	explicit		HostLogic		() = default;
	~HostLogic		() = default;


	void				RemoveControl		( UIElement* control );

	void				RegisterControlName	( UIElement* control, const std::string& name );
	const std::string&	GetControlName		( UIElement* control );


	///@name GUI system interaction
	///@{
	void				LostFocus		();
	void				GotFocus		();

	void				OnResized		( uint16 newWidth, uint16 newHeight );
	void				OnMaximized		();
	void				OnMinimized		();
	///@}


public:

	void				HandleKeyInput			( const input::DeviceEvent& event, input::Device* device );
	void				HandleCharInput			( const input::DeviceEvent& event, input::Device* device );
	void				HandleMouseButtonInput	( const input::DeviceEvent& event, input::Device* device );
	void				HandleMouseWheelInput	( const input::DeviceEvent& event, input::Device* device );
	void				HandleMouseMoveInput	( const input::DeviceEvent& event, input::Device* device );

public:

	Size				GetMemorySize		();
};



}	// gui
}	// sw

