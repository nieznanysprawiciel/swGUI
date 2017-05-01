#pragma once
/**
@file HostWindow.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGUI/Native/INativeWindow.h"
#include "HostLogic.h"
#include "swGUI/Core/Controls/TopLevelControl.h"

#include "swInputLibrary/InputCore/IInput.h"

#include <vector>
#include <map>

class IGraphicAPIInitializer;



namespace sw {
namespace gui
{

/**@brief Root class for controls hierarchy, contains native window.

This class connects native window and gui windows. GUI system logic is redirected to HostLogic class.
HostWindow is responsible for rendering and presenting content on native window by using render target and swap chain.

@ingroup GUICore
@ingroup ControlsFramework*/
class HostWindow : public UIElement
{
private:

	INativeWindow*				m_nativeWindow;
	input::IInput*				m_input;
	ResourceManager*			m_resourceManager;

	ResourcePtr< RenderTargetObject >	m_renderTarget;
	ResourcePtr< SwapChain >			m_swapChain;

	HostLogic					m_hostLogic;

protected:
public:
	explicit		HostWindow	( INativeWindow* nativeWindow, input::IInput* input, ResourceManager* resourceManager, IGraphicAPIInitializer* graphicApi );
	virtual			~HostWindow	();


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

	void				HandleInput		();
	///@}


	// Inherited via UIElement
	virtual bool		HitTest			( const Position& point )		override;
	virtual void		OnRender		( DrawingContext& context )		override;
	virtual Size2D		Measure			( Size2D availableSize )		override;
	virtual void		Arrange			( Rect& finalRect )				override;
	virtual Size		GetNumChildren	()								override;
	virtual UIElement*	GetUIChild		( Size idx )					override;
	virtual bool		AddChild		( UIElementOPtr&& child )		override;


};


}	// gui
}	// sw
