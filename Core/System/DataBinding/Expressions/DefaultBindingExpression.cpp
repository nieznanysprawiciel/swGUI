#include "DefaultBindingExpression.h"



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
	return Nullable<BindingTarget>();
}

// ================================ //
//
BindingExpressionType					DefaultBindingExpression::GetExpressionType		() const
{
	return BindingExpressionType::DataContext;
}


}	// gui
}	// sw

