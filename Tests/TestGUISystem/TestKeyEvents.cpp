#include "swCommonLib/External/Catch/catch.hpp"

#include "swGUI/TestFramework/TestFramework.h"

using namespace sw;
using namespace sw::gui;




TEST_CASE( "KeyUp event" )
{
	TestFramework framework( 0, nullptr );

	HostWindow* window = framework.CreateNativeHostWindow( 400, 400, "TestWindow" );
	input::EventCapture* eventCapturer = framework.GetEventCapturer();

	framework.OnFocusChanged( window->GetNativeWindow(), true );




}
