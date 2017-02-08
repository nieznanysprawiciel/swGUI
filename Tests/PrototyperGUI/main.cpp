#include "swGUI/System/GUISystem.h"
#include "swGUI/System/Windows/WinAPI/WinAPIGUI.h"

#include "Application.h"


int main( int argc, char** argv )
{
	Application app( argc, argv, GUI::WinAPIGUI::Create() );
	app.Init();

	return app.MainLoop();
}