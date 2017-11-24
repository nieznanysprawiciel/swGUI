#pragma once

#include "swCommonLib/Common/RTTR.h"

#include <string>


namespace sw
{



/**@brief */
class Animal
{
	RTTR_ENABLE();
	RTTR_REGISTRATION_FRIEND;
private:

	std::string			m_name;

protected:
public:
	explicit		Animal		() = default;
	virtual			~Animal		();

};





}	// sw


