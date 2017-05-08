#pragma once
/**
@file MouseMoveEventArgs.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "MouseEventArgs.h"

#include "swInputLibrary/InputCore/MouseDevice.h"



namespace sw {
namespace gui
{


/**@brief Mouse moved event.
@ingroup InputEvents*/
struct MouseMoveEventArgs : public MouseEventArgs
{
	RTTR_ENABLE( MouseEventArgs )
public:

	uint16			MouseDeltaX;
	uint16			MouseDeltaY;

public:

	explicit MouseMoveEventArgs( input::MouseDevice* device, uint16 deltaX, uint16 deltaY )
		:	MouseEventArgs( device )
		,	MouseDeltaX( deltaX )
		,	MouseDeltaY( deltaY )
	{}
};

DEFINE_OPTR_TYPE( MouseMoveEventArgs );

}	// gui
}	// sw

