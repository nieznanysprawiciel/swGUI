#pragma once

#include "swGUI/Core/System/Events/Input/KeyboardEventArgs.h"


namespace sw {
namespace gui
{

struct KeyEventArgs : public KeyboardEventArgs
{
	RTTR_ENABLE( KeyboardEventArgs )
public:

	const input::KeyState*				State;
	input::Keyboard::PhysicalKeys		Key;
	bool								IsUp;
	bool								IsDown;

public:

	explicit KeyEventArgs( input::KeyboardDevice* device, input::Keyboard::PhysicalKeys key )
		:	KeyboardEventArgs( device )
		,	State( &device->GetState()[ key ] )
		,	Key( key )
		,	IsUp( device->GetState()[ key ].IsUp() )
		,	IsDown( device->GetState()[ key ].IsPressed() )
	{}

};

}	// gui
}	// sw
