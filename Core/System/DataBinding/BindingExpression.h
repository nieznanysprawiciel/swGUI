#pragma once
/**
@file BindingExpression.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Engine.
*/


#include "swCommonLib/Common/TypesDefinitions.h"

#include <string>


namespace sw {
namespace gui
{


/**@brief Class can evaluate binding address to right property and object.
@ingroup DataBindingSystem*/
class BindingExpression
{
public:

	/**@brief Binding expressions types.
	@todo We should implement some other types here like Collection binding, StaticResource binding, ElementName...
	@ingroup DataBindingSystem*/
	enum class ExpressionType : uint8
	{
		DataContext,			///< Find property by path beginning in current DataContext.
		StaticResource,			///< Bind to property of static resource defined in xml.
		Self,					///< Binding to property of the same object.
		FindAncestor,			///< Binding to one of ancestors in controls hierarchy.
		TemplatedParent,		///< Binding to control which the template is applied to.
		PreviousData			///< Maybe won't be supported.
	};

private:

	std::string			m_path;
	TypeID				m_ancestorType;
	uint16				m_ancestorLevels;
	ExpressionType		m_exprType;

public:

};

}	// gui
}	// sw
