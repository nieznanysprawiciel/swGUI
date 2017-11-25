#include "swCommonLib/External/Catch/catch.hpp"


#include "swGUI/Core/System/DataBinding/Expressions/DefaultBindingExpression.h"

#include "swGUI/Tests/TestBindings/Classes/Animal.h"

#include <memory>


using namespace sw;


// ================================ //
// Evalute binding target by using DefaultBindingExpression. Pass path containing only single property name.
// Set simple base class as DataContext. propertyOwner parameter should be ignored.
TEST_CASE( "PathEvaluation_OneElementPath", "[GUI][BindingSystem][Expressions]" )
{
	std::unique_ptr< Animal > animal = std::unique_ptr< Animal >( new Animal );
	auto bindingTarget = gui::DefaultBindingExpression::EvaluateRelativeProperty( animal.get(), "Name" );

	REQUIRE( bindingTarget.IsValid() );
	
	CHECK( bindingTarget.Get().Property.get_name() == "Name" );

	// Property types is reference wrapper to string, so we must check wrapped type.
	CHECK( bindingTarget.Get().Property.get_type().get_wrapped_type() == TypeID::get< std::string >() );
	CHECK( bindingTarget.Get().Property.get_declaring_type() == TypeID::get< sw::Animal >() );

	CHECK( bindingTarget.Get().Target.get_value< Animal* >() == animal.get() );
}


// ================================ //
// Evalute binding target by using DefaultBindingExpression. Pass path to non existing property.
// EvaluateExpression should return invalid BindingTarget nullable.
TEST_CASE( "PathEvaluation_PassNonExistingPropertyPath", "[GUI][BindingSystem][Expressions]" )
{
	std::unique_ptr< Animal > animal = std::unique_ptr< Animal >( new Animal );
	auto bindingTarget = gui::DefaultBindingExpression::EvaluateRelativeProperty( animal.get(), "NonExistingProperty" );

	REQUIRE_FALSE( bindingTarget.IsValid() );
}

// ================================ //
//
TEST_CASE( "PathEvaluation_PassNullDataContext", "[GUI][BindingSystem][Expressions]" )
{
	auto bindingTarget = gui::DefaultBindingExpression::EvaluateRelativeProperty( rttr::variant( nullptr ), "NonExistingProperty" );

	REQUIRE_FALSE( bindingTarget.IsValid() );
}

