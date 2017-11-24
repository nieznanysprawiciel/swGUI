#include "Animal.h"



RTTR_REGISTRATION
{
	rttr::registration::class_< sw::Animal >( "sw::Animal" )
	.property( "Name", &sw::Animal::m_name ) BIND_AS_REF;
	
}



// ================================ //
// Add one class to pull registration code into library.
sw::Animal::~Animal()
{}
