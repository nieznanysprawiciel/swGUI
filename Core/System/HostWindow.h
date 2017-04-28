#pragma once

#include "swGUI/Native/INativeWindow.h"
#include "swGUI/Core/Controls/UIElement.h"
#include "swGUI/Core/Controls/TopLevelControl.h"

#include "swInputLibrary/InputCore/IInput.h"

#include <vector>
#include <map>

class IGraphicAPIInitializer;



namespace sw {
namespace gui
{

/**@brief Root class for controls hierarchy, contains native window.

@ingroup EngineGUI

Children of this class must inherit from TopLevelControl. This means that top level classes must be
Windows, ContextMenus, PopupMenus or others similar.*/
class HostWindow
{
private:

	INativeWindow*				m_nativeWindow;
	input::IInput*				m_input;
	ResourceManager*			m_resourceManager;

	EngineObject*				m_dataContext;

	std::vector< UIElement* >	m_mousePath;		///< Controls hierarchy that captured mouse in this frame.
	std::vector< UIElement* >	m_focusPath;		///< Controls hierarchy that have focus in this frame.
	std::vector< UIElement* >	m_invalidated;		///< Controls which needs to be redrawn in this frame.

	std::vector< UIElement* >			m_controlTree;	///< Top level controls.

	ResourcePtr< RenderTargetObject >	m_renderTarget;
	ResourcePtr< SwapChain >			m_swapChain;

	///@name Controls info
	///@{

	/// Map containing windows names. Most controls don't have name, so it's better to store
	/// them separatly, to lower memory consumption.
	std::map< UIElement*, std::string >	m_controlsNames;

	///@}

protected:
public:
	explicit		HostWindow	( INativeWindow* nativeWindow, input::IInput* input, ResourceManager* resourceManager, IGraphicAPIInitializer* graphicApi );
	~HostWindow	();


	Size				GetMemorySize		();


	EngineObject*&		DataContext			();
	void				RemoveControl		( UIElement* control );

	void				RegisterControlName	( UIElement* control, const std::string& name );
	const std::string&	GetControlName		( UIElement* control );


	ResourcePtr< RenderTargetObject >	GetRenderTarget		();
	ResourcePtr< SwapChain >			GetSwapChain		();

	INativeWindow*						GetNativeWindow		();

public:
	///@name GUI system interaction
	///@{
	void				LostFocus		();
	void				GotFocus		();

	void				OnResized		( uint16 newWidth, uint16 newHeight );
	void				OnMaximized		();
	void				OnMinimized		();
	///@}

};


}	// gui
}	// sw
