#pragma once


#include "swCommonLib/Common/RTTR.h"

#include "BindingMode.h"
#include "BindingExpression.h"
#include "Binding.h"


#include <string>
#include <vector>



namespace sw {
namespace gui
{

struct BindingInfo;
DEFINE_PTR_TYPE( BindingInfo )


/**@brief Holds information about all bindings to property.
@ingroup DataBindingSystem*/
struct BindingsInfo
{
	Binding					PropertyBinding;


	std::vector< BindingInfoPtr >	BoundProperties;	///< All properties receiving values from this one.
};



}	// gui
}	// sw



