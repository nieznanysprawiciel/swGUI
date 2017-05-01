#pragma once

#include "swGUI/Core/System/Events/IEventArgs.h"

#include "swInputLibrary/InputCore/Device.h"


namespace sw {
namespace gui
{

struct InputEventArgs : public IEventArgs
{
	RTTR_ENABLE( IEventArgs )
public:

	input::Device*					Device;			///< Device which produced this event.

public:

	InputEventArgs( input::Device* device )
		: Device( device )
	{}
};

}	// gui
}	// sw
