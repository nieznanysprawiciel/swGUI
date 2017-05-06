#include "swCommonLib/External/Catch/catch.hpp"

#include "swGUI/TestFramework/TestFramework.h"

using namespace sw;
using namespace sw::gui;


std::vector< input::Keyboard::PhysicalKeys >	upKeys;
std::vector< input::Keyboard::PhysicalKeys >	downKeys;



// ================================ //
//
void		KeyEventReceived			( UIElement* sender, KeyEventArgs* e )
{
	CHECK( e->IsUp != e->IsDown );

	if( e->IsUp )
		upKeys.push_back( e->Key );
	if( e->IsDown )
		downKeys.push_back( e->Key );
	
	CHECK( e->State[ e->Key ].IsUp() == e->IsUp );
	CHECK( e->State[ e->Key ].IsPressed() == e->IsDown );

	CHECK( e->State[ e->Key ].IsKeyUpEvent() == e->IsUp );
	CHECK( e->State[ e->Key ].IsKeyDownEvent() == e->IsDown );
}

// ================================ //
//
void		PreviewKeyEventReceived		( UIElement* sender, KeyEventArgs* e )
{

}


TEST_CASE( "KeyUp event" )
{
	TestFramework framework( 0, nullptr );
	framework.Init();

	HostWindow* window = framework.CreateNativeHostWindow( 400, 400, "TestWindow" );
	input::EventCapture* eventCapturer = framework.GetEventCapturer();

	framework.OnFocusChanged( window->GetNativeWindow(), true );

	window->KeyUp() += EventDelegate< KeyEventArgs >( &KeyEventReceived );
	window->KeyDown() += EventDelegate< KeyEventArgs >( &KeyEventReceived );

	window->PreviewKeyUp() += EventDelegate< KeyEventArgs >( &KeyEventReceived );
	window->PreviewKeyDown() += EventDelegate< KeyEventArgs >( &KeyEventReceived );


// ================================ //
//
	std::vector< input::Keyboard::PhysicalKeys >	testUpKeys;
	std::vector< input::Keyboard::PhysicalKeys >	testDownKeys;


// ================================ //
//
	eventCapturer->QueueDownKeyEvent( input::Keyboard::PhysicalKeys::KEY_J );
	testDownKeys.push_back( input::Keyboard::PhysicalKeys::KEY_J );

	framework.TesterMainStep();

// ================================ //
// Check vectors content.

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
