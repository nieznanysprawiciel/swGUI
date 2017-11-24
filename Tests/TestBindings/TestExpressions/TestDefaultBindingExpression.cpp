#include "swCommonLib/External/Catch/catch.hpp"


#include "swGUI/Core/System/DataBinding/Expressions/DefaultBindingExpression.h"

#include "swGUI/Tests/TestBindings/Classes/Animal.h"



using namespace sw;


// ================================ //
// Evalute binding target by using DefaultBindingExpression. Pass path containing only single property name.
// Set simple base class as DataContext. propertyOwner parameter should be ignored.
TEST_CASE( "DefaultBindingExpression_OneElementPath", "[GUI][BindingSystem][Expressions]" )
{
	gui::DefaultBindingExpressionPtr expression = std::make_shared< gui::DefaultBindingExpression >( "Name" );

	Animal* animal = new Animal;
	auto bindingTarget = expression->EvaluateExpression( animal, rttr::variant() );

	REQUIRE( bindingTarget.IsValid() );
	CHECK( bindingTarget.Get().Property.get_name() == "Name" );
	CHECK( bindingTarget.Get().Property.get_type() == TypeID::get< std::string >() );
}



