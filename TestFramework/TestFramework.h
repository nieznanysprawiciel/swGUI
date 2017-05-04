#pragma once
/**
@file TestFramework.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGUI/Core/System/GUISystem.h"
#include "swInputLibrary/InputCore/Debugging/EventCapture.h"



namespace sw {
namespace gui
{


/**@brief */
class TestFramework : public GUISystem
{
private:

	input::EventCapture*		m_eventCapture;

protected:
public:
	explicit		TestFramework		( int argc, char** argv );
	virtual			~TestFramework		() = default;


	virtual	void				Initialize			();


public:

	///@name Test writer API
	///@{

	/**@brief Returns event capturer which can emulate events.*/
	input::EventCapture*		GetEventCapturer	() { return m_eventCapture; }

	/**@brief Calls main loop but returns after making full step.*/
	bool						TesterMainStep		();

	///@}

private:
	bool			InitTesterNativeGUI		();
	void			InitTesterDebugInput	();
};


}	// gui
}	// sw


