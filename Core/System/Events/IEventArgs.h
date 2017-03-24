#pragma once

#include "swCommonLib/Common/RTTR.h"


namespace sw {
namespace gui
{

/**@brief Base class for events.*/
struct IEventArgs
{
	RTTR_ENABLE()
public:
	IEventArgs()
		:	Handled( false )
	{}
public:
	bool			Handled;		///< Mark event as handled to stop further processing.
};


}	// gui
}	// sw

