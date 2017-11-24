#include "DefaultBindingExpression.h"

#include "swCommonLib/Common/Properties/Properties.h"


namespace sw {
namespace gui
{



// ================================ //
//
DefaultBindingExpression::DefaultBindingExpression		( const std::string & bindingPath )
	:	BindingExpression( bindingPath )
{}


// ================================ //
//
Nullable< BindingTarget >				DefaultBindingExpression::EvaluateExpression		( const rttr::variant& dataContext, const rttr::variant& propertyOwner ) const
{
	auto propObjPair = Properties::GetProperty( dataContext, m_path );

	if( propObjPair.first.is_valid() && propObjPair.second.is_valid() )
		return BindingTarget( propObjPair.first, propObjPair.second );

	/// @todo Make exception for this error.
	return Nullable< BindingTarget >();
}

// ================================ //
//
BindingExpressionType					DefaultBindingExpression::GetExpressionType		() const
{
	return BindingExpressionType::DataContext;
}


}	// gui
}	// sw

