#include "swCommonLib/External/Catch/catch.hpp"

#include "swGUI/Core/Controls/UIElement.h"
#include "swGUI/Core/System/Events/IEventArgs.h"


using namespace sw::gui;


// ================================ //
//
struct ValidationEventArgs : public IEventArgs
{
	RTTR_ENABLE( IEventArgs );
};
DEFINE_OPTR_TYPE( ValidationEventArgs );


// ================================ //
//
struct UnusedEventArgs : public IEventArgs
{
	RTTR_ENABLE( IEventArgs );
};
DEFINE_OPTR_TYPE( UnusedEventArgs );


// ================================ //
//
RTTR_REGISTRATION
{
	rttr::registration::class_< ValidationEventArgs >( "ValidationEventArgs" );
	rttr::registration::class_< UnusedEventArgs >( "UnusedEventArgs" );
}


//====================================================================================//
//			Header	
//====================================================================================//

class TestUIElementClass : public sw::gui::UIElement
{
private:
public:
	// Event part
	REGISTER_EVENT_DECLARATION( ValidationStarted, RoutingStrategy::Direct, TestUIElementClass, ValidationEventArgs );
	REGISTER_EVENT_DECLARATION( UnusedEvent, RoutingStrategy::Direct, TestUIElementClass, UnusedEventArgs );
public:
	void		EventRaisingFunction		();

	/// Check functions.
	bool		ExistsDelegatesContainer	( EventType eventID );

#pragma region Inherited


	// Inherited via UIElement
	virtual bool HitTest( const Position & point ) override
	{
		return false;
	}

	virtual void OnRender( DrawingContext & context ) override
	{}

	virtual Size2D Measure( Size2D availableSize ) override
	{
		return Size2D();
	}

	virtual void Arrange( Rect & finalRect ) override
	{}

	virtual Size GetNumChildren() override
	{
		return Size();
	}

	virtual UIElement * GetUIChild( Size idx ) override
	{
		return nullptr;
	}

#pragma endregion


};


//====================================================================================//
//			Definitions	
//====================================================================================//


REGISTER_EVENT_DEFINITION( ValidationStarted, RoutingStrategy::Direct, TestUIElementClass, ValidationEventArgs );
REGISTER_EVENT_DEFINITION( UnusedEvent, RoutingStrategy::Direct, TestUIElementClass, UnusedEventArgs );


// ================================ //
//
void		TestUIElementClass::EventRaisingFunction		()
{
	bool result = ValidationStarted().RaiseEvent( this, ValidationEventArgsOPtr( new ValidationEventArgs() ) );
	CHECK( result );

	result = UnusedEvent().RaiseEvent( this, UnusedEventArgsOPtr( new UnusedEventArgs() ) );
	CHECK( result );
}

// ================================ //
//
bool		TestUIElementClass::ExistsDelegatesContainer	( EventType eventID )
{
	return m_eventHandlers.FindContainer( eventID ) ? true : false;
}



int validationDelegateCounter = 0;

// ================================ //
//
void		ValidationDelegate	( UIElement* sender, ValidationEventArgs* e )
{
	validationDelegateCounter++;
}


TEST_CASE( "Raising events" )
{
	TestUIElementClass testClass;

	testClass.ValidationStarted() += EventDelegate< ValidationEventArgs >( &ValidationDelegate );

	CHECK( testClass.ExistsDelegatesContainer( TestUIElementClass::sValidationStarted->ID ) );

	testClass.EventRaisingFunction();
	CHECK( validationDelegateCounter == 1 );
}

