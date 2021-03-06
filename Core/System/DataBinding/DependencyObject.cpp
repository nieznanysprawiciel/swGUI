/**
@file DependencyObject.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/
#include "swGUI/Core/stdafx.h"



#include "DependencyObject.h"


RTTR_REGISTRATION
{
	using namespace rttr;

	registration::class_< sw::gui::DependencyObject >( "sw::gui::DependencyObject" );


};



namespace sw {
namespace gui
{


// ================================ //
//
DependencyObject::DependencyObject()
	: m_dataContext( nullptr )
{ }

// ================================ //
//
void			DependencyObject::SetDataContext		( const rttr::variant& dataContext )
{
	// Context propagation to children should be implemented in override in derived class.
	m_dataContext = dataContext;
}

// ================================ //
//
ReturnResult	DependencyObject::AddBinding			( BindingPtr binding )
{
	auto result = binding->UpdateBinding( m_dataContext );
	
	if( result.IsValid() )
		return m_bindingsList.AddBinding( binding );
	else
		return result;
}

// ================================ //
//
void			DependencyObject::AddBindingLink		( const BindingInfoPtr& bindingInfo )
{
	m_bindingsList.AddBindingLink( bindingInfo );
}




}	// gui
}	// sw

