#include "swCommonLib/External/Catch/catch.hpp"

#include "swGUI/Core/System/DataBinding/Binding.h"
#include "swGUI/Core/System/DataBinding/Expressions/DefaultBindingExpression.h"

#include "swCommonLib/TestUtils/TestClassHierarchy/Animals/Animal.h"
#include "swCommonLib/TestUtils/TestClassHierarchy/Animals/Mammals/Dog.h"

#include "swGUI/TestFramework/Utils/ClassesUI/DependencyPropsClass.h"

#include "swCommonLib/Common/Properties/Properties.h"

using namespace sw;



// ================================ //
//
TEST_CASE( "Binding_DependencyObject_BindSingleProperty", "[GUI][BindingSystem]" )
{
	std::unique_ptr< Dog > dog = std::unique_ptr< Dog >( new Dog );
	std::unique_ptr< gui::DependencyPropsClass > root = std::make_unique< gui::DependencyPropsClass >();

	root->SetDataContext( dog.get() );

	auto binding = gui::Binding::Create( "NumberItems", root.get(), "PhysicalProperties.Length", gui::BindingMode::OneWayToSource );

	REQUIRE( root->AddBinding( binding ).IsValid() );

	root->SetNumberItems( 333 );
	CHECK( dog->m_physicalProperties.Length == 333 );

	root->SetNumberItems( 7777 );
	CHECK( dog->m_physicalProperties.Length == 7777 );

	root->SetNumberItems( 33551 );
	CHECK( dog->m_physicalProperties.Length == 33551 );
}

// ================================ //
// 
TEST_CASE( "Binding_DependencyObject_MultipleBindings", "[GUI][BindingSystem]" )
{
	std::unique_ptr< Dog > dog = std::unique_ptr< Dog >( new Dog );
	std::unique_ptr< gui::DependencyPropsClass > root = std::make_unique< gui::DependencyPropsClass >();
	std::unique_ptr< gui::DependencyPropsClass > child1 = std::make_unique< gui::DependencyPropsClass >();
	std::unique_ptr< gui::DependencyPropsClass > child2 = std::make_unique< gui::DependencyPropsClass >();

	root->SetDataContext( dog.get() );
	child1->SetDataContext( root.get() );
	child2->SetDataContext( root.get() );

	auto binding1 = gui::Binding::Create( "NumberItems", root.get(), "PhysicalProperties.Height", gui::BindingMode::OneWayToSource );
	REQUIRE( root->AddBinding( binding1 ).IsValid() );

	auto binding2 = gui::Binding::Create( "NumberItems", child1.get(), "NumberItems", gui::BindingMode::OneWay );
	REQUIRE( child1->AddBinding( binding2 ).IsValid() );

	auto binding3 = gui::Binding::Create( "NumberItems", child2.get(), "NumberItems", gui::BindingMode::OneWay );
	REQUIRE( child2->AddBinding( binding3 ).IsValid() );

	root->SetNumberItems( 333 );
	CHECK( dog->m_physicalProperties.Height == 333 );
	CHECK( child1->GetNumberItems() == 333 );
	CHECK( child2->GetNumberItems() == 333 );

	root->SetNumberItems( 33551 );
	CHECK( dog->m_physicalProperties.Height == 33551 );
	CHECK( child1->GetNumberItems() == 33551 );
	CHECK( child2->GetNumberItems() == 33551 );
}


