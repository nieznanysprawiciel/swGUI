/**
@file ShaderBuilder.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "ShaderBuilder.h"




namespace sw {
namespace gui
{

// ================================ //
//
std::string			ShaderBuilder::BuildShader		( const std::string& shaderTemplate, const std::string& shaderFunction )
{
	// This version simply adds function at the beginning without checking content.
	return shaderFunction + shaderTemplate;
}


}	// gui
}	// sw