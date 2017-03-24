#include "swCommonLib/External/Catch/catch.hpp"

#include "swGUI/Core/Controls/UIElement.h"
#include "swGUI/Core/System/Events/IEventArgs.h"


using namespace sw::gui;


struct ValidationEventArgs : public IEventArgs
{
	RTTR_ENABLE( IEventArgs );
};

RTTR_REGISTRATION
{
	rttr::registration::class_< ValidationEventArgs >( "ValidationEventArgs" );
}


//====================================================================================//
//			Header	
//====================================================================================//

class TestUIElementClass : public sw::gui::UIElement
{
private:
public:
	// Event part
	static const RegisteredEvent* sValidationStarted;

	EventProxy< ValidationEventArgs >		ValidationStarted() { return EventProxy< ValidationEventArgs >( m_eventHandlers, sValidationStarted ); }

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


const RegisteredEvent* TestUIElementClass::sValidationStarted = EventsSystem::Get().RegisterEvent( "ValidationEvent", RoutingStrategy::Direct, TypeID::get< TestUIElementClass >(), TypeID::get< ValidationEventArgs >() );



// ================================ //
//
void		TestUIElementClass::EventRaisingFunction		()
{
	bool result = ValidationStarted().RaiseEvent( this, new ValidationEventArgs );
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

