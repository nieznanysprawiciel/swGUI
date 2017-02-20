#include "Sizeofs.h"


#include "swCommonLib/Common/TypesDefinitions.h"


#include <iostream>
#include <iomanip>


#include "swGUI/Core/System/GUISystem.h"
#include "swGUI/Core/Controls/IControl.h"
#include "swGUI/Core/Controls/UIElement.h"
#include "swGUI/Core/Controls/Visual.h"



const int NameSize = 60;


// ================================ //
//
template< typename Type >
void			PrintSizeofType		( std::ostream& stream )
{
	stream << typeid( Type ).name();
	stream << std::setw( NameSize );
	stream << sizeof( Type ) << std::endl;
}


// ================================ //
//
void			PrintSizeofs()
{
	std::cout << "Objects name" << std::setw( NameSize ) << "Sizeof" << std::endl;

	PrintSizeofType< sw::gui::IControl >( std::cout );
	PrintSizeofType< sw::gui::Visual >( std::cout );
	PrintSizeofType< sw::gui::UIElement >( std::cout );

}
