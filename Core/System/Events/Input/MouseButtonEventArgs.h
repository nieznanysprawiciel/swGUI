#pragma once

#include "MouseEventArgs.h"




namespace sw {
namespace gui
{


struct MouseButtonEventArgs : public MouseEventArgs
{
	RTTR_ENABLE( MouseEventArgs )
public:

	const input::KeyState*				State;
	input::Mouse::PhysicalButtons		Button;
	bool								IsUp;
	bool								IsDown;

public:
	explicit	MouseButtonEventArgs( input::MouseDevice* device, input::Mouse::PhysicalButtons button )
		:	MouseEventArgs( device )
		,	State( &device->GetState()[ button ] )
		,	IsUp( device->GetState()[ button ].IsUp() )
		,	IsDown( device->GetState()[ button ].IsPressed() )
	{}
};



}	// gui

}	// sw