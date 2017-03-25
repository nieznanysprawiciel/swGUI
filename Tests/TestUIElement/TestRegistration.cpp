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
	REGISTER_EVENT_DECLARATION( ValidationEnded, RoutingStrategy::Direct, TestUIElementClass, ValidationEventArgs );
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
REGISTER_EVENT_DEFINITION( ValidationEnded, RoutingStrategy::Direct, TestUIElementClass, ValidationEventArgs );
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
int valid1Counter = 0;
int valid2Counter = 0;
int valid3Counter = 0;
int valid4Counter = 0;


// ================================ //
//
void		CleanCounters()
{
	validationDelegateCounter = 0;
	valid1Counter = 0;
	valid2Counter = 0;
	valid3Counter = 0;
	valid4Counter = 0;
}

// ================================ //
//
void		ValidationDelegate	( UIElement* sender, ValidationEventArgs* e )
{
	validationDelegateCounter++;
	valid1Counter++;
}


// ================================ //
//
void		ValidationDelegate2	( UIElement* sender, ValidationEventArgs* e )
{
	validationDelegateCounter++;
	valid2Counter++;
}

// ================================ //
//
void		ValidationDelegate3	( UIElement* sender, ValidationEventArgs* e )
{
	validationDelegateCounter++;
	valid3Counter++;
}

// ================================ //
//
void		ValidationDelegate4	( UIElement* sender, ValidationEventArgs* e )
{
	validationDelegateCounter++;
	valid4Counter++;
}

//====================================================================================//
//			Test code	
//====================================================================================//


TEST_CASE( "Raising events" )
{
	CleanCounters();

	TestUIElementClass testClass;

	testClass.ValidationStarted() += EventDelegate< ValidationEventArgs >( &ValidationDelegate );

	CHECK( testClass.ExistsDelegatesContainer( TestUIElementClass::sValidationStarted->ID ) );
	CHECK( !testClass.ExistsDelegatesContainer( TestUIElementClass::sUnusedEvent->ID ) );

	testClass.EventRaisingFunction();
	CHECK( validationDelegateCounter == 1 );
	CHECK( valid1Counter == 1 );

	testClass.ValidationStarted() -= EventDelegate< ValidationEventArgs >( &ValidationDelegate );

	CHECK( !testClass.ExistsDelegatesContainer( TestUIElementClass::sValidationStarted->ID ) );
	CHECK( !testClass.ExistsDelegatesContainer( TestUIElementClass::sUnusedEvent->ID ) );
}


TEST_CASE( "Adding removing deelgates" )
{
	CleanCounters();

	TestUIElementClass testClass;

	testClass.ValidationStarted() += EventDelegate< ValidationEventArgs >( &ValidationDelegate );

	CHECK( testClass.ExistsDelegatesContainer( TestUIElementClass::sValidationStarted->ID ) );
	CHECK( !testClass.ExistsDelegatesContainer( TestUIElementClass::sUnusedEvent->ID ) );

	testClass.EventRaisingFunction();
	CHECK( validationDelegateCounter == 1 );
	CHECK( valid1Counter == 1 );
	CHECK( valid2Counter == 0 );
	CHECK( valid3Counter == 0 );
	CHECK( valid4Counter == 0 );

	// Add new delegate
	testClass.ValidationStarted() += EventDelegate< ValidationEventArgs >( &ValidationDelegate2 );
	CHECK( !testClass.ExistsDelegatesContainer( TestUIElementClass::sUnusedEvent->ID ) );
	testClass.EventRaisingFunction();

	CHECK( validationDelegateCounter == 3 );
	CHECK( valid1Counter == 2 );
	CHECK( valid2Counter == 1 );
	CHECK( valid3Counter == 0 );
	CHECK( valid4Counter == 0 );

	// Add new delegate
	testClass.ValidationStarted() += EventDelegate< ValidationEventArgs >( &ValidationDelegate3 );
	CHECK( !testClass.ExistsDelegatesContainer( TestUIElementClass::sUnusedEvent->ID ) );
	testClass.EventRaisingFunction();

	CHECK( validationDelegateCounter == 6 );
	CHECK( valid1Counter == 3 );
	CHECK( valid2Counter == 2 );
	CHECK( valid3Counter == 1 );
	CHECK( valid4Counter == 0 );

	// Add new delegate
	testClass.ValidationStarted() += EventDelegate< ValidationEventArgs >( &ValidationDelegate4 );
	CHECK( !testClass.ExistsDelegatesContainer( TestUIElementClass::sUnusedEvent->ID ) );
	testClass.EventRaisingFunction();

	CHECK( validationDelegateCounter == 10 );
	CHECK( valid1Counter == 4 );
	CHECK( valid2Counter == 3 );
	CHECK( valid3Counter == 2 );
	CHECK( valid4Counter == 1 );

	testClass.EventRaisingFunction();

	CHECK( validationDelegateCounter == 14 );
	CHECK( valid1Counter == 5 );
	CHECK( valid2Counter == 4 );
	CHECK( valid3Counter == 3 );
	CHECK( valid4Counter == 2 );

	// Delete delegate
	testClass.ValidationStarted() -= EventDelegate< ValidationEventArgs >( &ValidationDelegate );
	CHECK( testClass.ExistsDelegatesContainer( TestUIElementClass::sValidationStarted->ID ) );
	CHECK( !testClass.ExistsDelegatesContainer( TestUIElementClass::sUnusedEvent->ID ) );

	testClass.EventRaisingFunction();

	CHECK( validationDelegateCounter == 17 );
	CHECK( valid1Counter == 5 );
	CHECK( valid2Counter == 5 );
	CHECK( valid3Counter == 4 );
	CHECK( valid4Counter == 3 );

	// Delete delegate
	testClass.ValidationStarted() -= EventDelegate< ValidationEventArgs >( &ValidationDelegate2 );
	CHECK( testClass.ExistsDelegatesContainer( TestUIElementClass::sValidationStarted->ID ) );
	CHECK( !testClass.ExistsDelegatesContainer( TestUIElementClass::sUnusedEvent->ID ) );

	testClass.EventRaisingFunction();

	CHECK( validationDelegateCounter == 19 );
	CHECK( valid1Counter == 5 );
	CHECK( valid2Counter == 5 );
	CHECK( valid3Counter == 5 );
	CHECK( valid4Counter == 4 );

	// Delete delegate
	testClass.ValidationStarted() -= EventDelegate< ValidationEventArgs >( &ValidationDelegate3 );
	CHECK( testClass.ExistsDelegatesContainer( TestUIElementClass::sValidationStarted->ID ) );
	CHECK( !testClass.ExistsDelegatesContainer( TestUIElementClass::sUnusedEvent->ID ) );

	testClass.EventRaisingFunction();

	CHECK( validationDelegateCounter == 20 );
	CHECK( valid1Counter == 5 );
	CHECK( valid2Counter == 5 );
	CHECK( valid3Counter == 5 );
	CHECK( valid4Counter == 5 );

	// Delete delegate
	testClass.ValidationStarted() -= EventDelegate< ValidationEventArgs >( &ValidationDelegate4 );
	CHECK( !testClass.ExistsDelegatesContainer( TestUIElementClass::sValidationStarted->ID ) );
	CHECK( !testClass.ExistsDelegatesContainer( TestUIElementClass::sUnusedEvent->ID ) );

	testClass.EventRaisingFunction();

	CHECK( validationDelegateCounter == 20 );
	CHECK( valid1Counter == 5 );
	CHECK( valid2Counter == 5 );
	CHECK( valid3Counter == 5 );
	CHECK( valid4Counter == 5 );
}

