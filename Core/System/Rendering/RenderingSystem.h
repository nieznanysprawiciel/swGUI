#pragma once
/**
@file RenderingSystem.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGraphicAPI/Rendering/IGraphicAPIInitializer.h"
#include "swGraphicAPI/Rendering/IRenderer.h"
#include "swGraphicAPI/ResourceManager/ResourceManager.h"

#include "swGraphicAPI/Resources/RasterizerState.h"
#include "swGraphicAPI/Resources/DepthStencilState.h"
#include "swGraphicAPI/Resources/BlendingState.h"

#include "swGUI/Core/System/Rendering/Shading/ShaderProvider.h"
#include "swGUI/Core/System/Config/PathsManager.h"

#include "swGUI/Core/Controls/Visual.h"
#include "swGUI/Core/System/Rendering/Drawings/IDrawing.h"



/**@defgroup RenderingSystem Rendering System
@ingroup GUICore*/


DEFINE_OPTR_TYPE( IRenderer );

namespace sw {
namespace gui
{

class HostWindow;


/**@brief GUI rendering system.

@ingroup RenderingSystem*/
class RenderingSystem
{
private:

	IRendererOPtr		m_renderer;
	ResourceManager*	m_resourceManager;
	ShaderProvider		m_shaderProvider;

private:

	// Rendering state objects
	ResourcePtr< RasterizerState >		m_rasterizerState;
	ResourcePtr< DepthStencilState >	m_depthState;

	ResourcePtr< BlendingState >		m_transparentBlendState;
	ResourcePtr< BlendingState >		m_opaqueBlendState;

protected:
public:
	explicit		RenderingSystem		( ResourceManager* resourceManager, PathsManager* pathsManager, IRendererOPtr&& renderer );
					~RenderingSystem	() = default;

	/**@brief Returns renderer.
	You probably don't need it. Use only if you write graphic application which renders something by itself.
	You are not owner of this object.*/
	IRenderer*			GetRenderer			() const			{ return m_renderer.get(); }

	/**@brief Returns internal ShaderProvider object.*/
	ShaderProvider*		GetShaderProvider	()					{ return &m_shaderProvider; }

public:

	///@name Rendering
	///@{
	void			RenderTree			( HostWindow* host );

	void			Render				( const Visual* visual );
	void			Render				( IDrawing* drawing );


	///@}

private:

	void			InitializeGraphicState		( ResourceManager* rm );
};

DEFINE_OPTR_TYPE( RenderingSystem );


}	// gui
}	// sw

