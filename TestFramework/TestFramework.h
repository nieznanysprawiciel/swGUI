#pragma once
/**
@file TestFramework.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGUI/Core/System/GUISystem.h"


namespace sw {
namespace gui
{


/**@brief */
class TestFramework : public GUISystem
{
private:
protected:
public:
	explicit		TestFramework		() = default;
	~TestFramework	() = default;


	virtual	void	Initialize		();
};


}	// gui
}	// sw


