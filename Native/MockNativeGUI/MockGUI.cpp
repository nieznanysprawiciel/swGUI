/**
@file MockGUI.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/



#include "MockGUI.h"
#include "MockWindow.h"




namespace sw {
namespace gui
{



// ================================ //
//
MockGUI::MockGUI()
{}


/**@brief Creates WinAPIGUI object.*/
MockGUI*		MockGUI::Create()
{
	return new MockGUI();
}



//====================================================================================//
//			Window creation	
//====================================================================================//



// ================================ //
/// @todo In future MockGUI could work together with DebugInput.
sw::input::IInput*		MockGUI::UseNativeInput()
{
	return nullptr;
}



/**@copydoc INativeGUI::CreateWindow*/
INativeWindow*	MockGUI::CreateWindow		( NativeWindowDescriptor& descriptor )
{
	MockWindow* newWindow = MockWindow::CreateWindowInstance( descriptor );
	return newWindow;
}


/**@copydoc INativeGUI::Init*/
bool		MockGUI::Init				( const NativeGUIInitData& initData )
{
	assert( !initData.FocusChanged.empty() );

	m_initData = initData;
	return true;
}



//====================================================================================//
//			Window Message handler
//====================================================================================//


/**@copydoc INativeGUI::MainLoop*/
bool		MockGUI::MainLoop                 ( bool blockingMode )
{
	return true;
}



}	// gui
}	// sw
