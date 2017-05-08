#include "swCommonLib/External/Catch/catch.hpp"

#include "swGUI/TestFramework/TestFramework.h"

using namespace sw;
using namespace sw::gui;


std::vector< input::Mouse::PhysicalButtons >	upKeys;
std::vector< input::Mouse::PhysicalButtons >	downKeys;



// ================================ //
//
void		MouseEventReceived			( UIElement* sender, MouseButtonEventArgs* e )
{
	CHECK( e->IsUp != e->IsDown );

	if( e->IsUp )
		upKeys.push_back( e->Button );
	if( e->IsDown )
		downKeys.push_back( e->Button );
	
	CHECK( e->State.IsUp() == e->IsUp );
	CHECK( e->State.IsPressed() == e->IsDown );

	CHECK( e->State.IsKeyUpEvent() == e->IsUp );
	CHECK( e->State.IsKeyDownEvent() == e->IsDown );

	CHECK( e->Mouse->GetState()[ e->Button ].IsUp() == e->IsUp );
	CHECK( e->Mouse->GetState()[ e->Button ].IsPressed() == e->IsDown );

	CHECK( e->Mouse->GetState()[ e->Button ].IsKeyUpEvent() == e->IsUp );
	CHECK( e->Mouse->GetState()[ e->Button ].IsKeyDownEvent() == e->IsDown );
}

// ================================ //
//
void		PreviewKeyEventReceivedHandled		( UIElement* sender, MouseButtonEventArgs* e )
{
	MouseEventReceived( sender, e );
	e->Handled = true;
}

// ================================ //
//
void		CheckVectorsContent					( const std::vector< input::Mouse::PhysicalButtons >& testUpKeys, const std::vector< input::Mouse::PhysicalButtons >& testDownKeys )
{
	CHECK( upKeys.size() == testUpKeys.size() );
	for( Size i = 0; i < std::min( upKeys.size(), testUpKeys.size() ); ++i )
	{
		INFO( i );
		CHECK( upKeys[ i ] == testUpKeys[ i ] );
	}

	CHECK( downKeys.size() == testDownKeys.size() );
	for( Size i = 0; i < std::min( downKeys.size(), testDownKeys.size() ); ++i )
	{
		INFO( i );
		CHECK( downKeys[ i ] == testDownKeys[ i ] );
	}
}



// ================================ //
//
TEST_CASE( "MouseButtonUp/MouseButtonDown event" )
{
	// Initialize framework.
	TestFramework framework( 0, nullptr );
	framework.Init();

	// Create main window (fake window) and get input::EventCapture. 
	HostWindow* window = framework.CreateNativeHostWindow( 400, 400, "TestWindow" );
	input::EventCapture* eventCapturer = framework.GetEventCapturer();

	// Set focus to window.
	framework.OnFocusChanged( window->GetNativeWindow(), true );

	// Add event handlers to tested events.
	window->MouseDown() += EventDelegate< MouseButtonEventArgs >( &MouseEventReceived );
	window->MouseUp() += EventDelegate< MouseButtonEventArgs >( &MouseEventReceived );

	window->PreviewMouseUp() += EventDelegate< MouseButtonEventArgs >( &MouseEventReceived );
	window->PreviewMouseDown() += EventDelegate< MouseButtonEventArgs >( &MouseEventReceived );


// ================================ //
//
	std::vector< input::Mouse::PhysicalButtons >	testUpKeys;
	std::vector< input::Mouse::PhysicalButtons >	testDownKeys;


// ================================ //
// Test single down event
	eventCapturer->QueueMouseClick( input::Mouse::PhysicalButtons::LEFT_BUTTON );
	testDownKeys.push_back( input::Mouse::PhysicalButtons::LEFT_BUTTON );			// PreviewKeyDown
	testDownKeys.push_back( input::Mouse::PhysicalButtons::LEFT_BUTTON );			// KeyDown

	framework.TesterMainStep();
	CheckVectorsContent( testUpKeys, testDownKeys );


// ================================ //
// Test up and down event
	eventCapturer->QueueMouseUp( input::Mouse::PhysicalButtons::LEFT_BUTTON );
	testUpKeys.push_back( input::Mouse::PhysicalButtons::LEFT_BUTTON );			// PreviewKeyDown
	testUpKeys.push_back( input::Mouse::PhysicalButtons::LEFT_BUTTON );			// KeyDown

	eventCapturer->QueueMouseClick( input::Mouse::PhysicalButtons::RIGHT_BUTTON );
	testDownKeys.push_back( input::Mouse::PhysicalButtons::RIGHT_BUTTON );			// PreviewKeyDown
	testDownKeys.push_back( input::Mouse::PhysicalButtons::RIGHT_BUTTON );			// KeyDown

	framework.TesterMainStep();
	CheckVectorsContent( testUpKeys, testDownKeys );

// ================================ //
// Test multiple events in row in the same frame
	eventCapturer->QueueMouseUp( input::Mouse::PhysicalButtons::RIGHT_BUTTON );
	testUpKeys.push_back( input::Mouse::PhysicalButtons::RIGHT_BUTTON );			// PreviewKeyDown
	testUpKeys.push_back( input::Mouse::PhysicalButtons::RIGHT_BUTTON );			// KeyDown

	eventCapturer->QueueMouseClick( input::Mouse::PhysicalButtons::MIDDLE_BUTTON );
	testDownKeys.push_back( input::Mouse::PhysicalButtons::MIDDLE_BUTTON );			// PreviewKeyDown
	testDownKeys.push_back( input::Mouse::PhysicalButtons::MIDDLE_BUTTON );			// KeyDown

	eventCapturer->QueueMouseClick( input::Mouse::PhysicalButtons::RIGHT_BUTTON );
	testDownKeys.push_back( input::Mouse::PhysicalButtons::RIGHT_BUTTON );			// PreviewKeyDown
	testDownKeys.push_back( input::Mouse::PhysicalButtons::RIGHT_BUTTON );			// KeyDown

	eventCapturer->QueueMouseUp( input::Mouse::PhysicalButtons::MIDDLE_BUTTON );
	testUpKeys.push_back( input::Mouse::PhysicalButtons::MIDDLE_BUTTON );			// PreviewKeyDown
	testUpKeys.push_back( input::Mouse::PhysicalButtons::MIDDLE_BUTTON );			// KeyDown

	eventCapturer->QueueMouseUp( input::Mouse::PhysicalButtons::RIGHT_BUTTON );
	testUpKeys.push_back( input::Mouse::PhysicalButtons::RIGHT_BUTTON );			// PreviewKeyDown
	testUpKeys.push_back( input::Mouse::PhysicalButtons::RIGHT_BUTTON );			// KeyDown

	framework.TesterMainStep();
	CheckVectorsContent( testUpKeys, testDownKeys );

// ================================ //
// Mark event as handled

	window->PreviewMouseUp() -= EventDelegate< MouseButtonEventArgs >( &MouseEventReceived );
	window->PreviewMouseDown() -= EventDelegate< MouseButtonEventArgs >( &MouseEventReceived );

	window->PreviewMouseUp() -= EventDelegate< MouseButtonEventArgs >( &PreviewKeyEventReceivedHandled );
	window->PreviewMouseDown() -= EventDelegate< MouseButtonEventArgs >( &PreviewKeyEventReceivedHandled );


// ================================ //
// Send some events
	eventCapturer->QueueMouseClick( input::Mouse::PhysicalButtons::LEFT_BUTTON );
	testDownKeys.push_back( input::Mouse::PhysicalButtons::LEFT_BUTTON );			// PreviewKeyDown

	eventCapturer->QueueMouseClick( input::Mouse::PhysicalButtons::RIGHT_BUTTON );
	testDownKeys.push_back( input::Mouse::PhysicalButtons::RIGHT_BUTTON );			// PreviewKeyDown

	eventCapturer->QueueMouseUp( input::Mouse::PhysicalButtons::LEFT_BUTTON );
	testUpKeys.push_back( input::Mouse::PhysicalButtons::LEFT_BUTTON );			// PreviewKeyDown

	eventCapturer->QueueMouseUp( input::Mouse::PhysicalButtons::RIGHT_BUTTON );
	testUpKeys.push_back( input::Mouse::PhysicalButtons::RIGHT_BUTTON );			// PreviewKeyDown

	framework.TesterMainStep();
	CheckVectorsContent( testUpKeys, testDownKeys );


// ================================ //
// Check state after Main loop

	eventCapturer->QueueMouseClick( input::Mouse::PhysicalButtons::MIDDLE_BUTTON );
	testDownKeys.push_back( input::Mouse::PhysicalButtons::MIDDLE_BUTTON );			// PreviewKeyDown

	// Make two loop steps to 
	framework.TesterMainStep();
	framework.TesterMainStep();
	CheckVectorsContent( testUpKeys, testDownKeys );

	auto& mouse = framework.GetInput()->GetMouseDevice()[ 0 ];
	const input::KeyState& state = mouse->GetState()[ input::Mouse::PhysicalButtons::MIDDLE_BUTTON ];

	CHECK( state.IsKeyDownEvent() == false );
	CHECK( state.IsKeyUpEvent() == false );
	CHECK( state.IsPressed() == true );
	CHECK( state.IsUp() == false );
}
