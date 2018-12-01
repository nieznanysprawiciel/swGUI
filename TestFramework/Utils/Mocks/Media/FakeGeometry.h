#pragma once
/**
@file FakeGeometry.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swGUI/Core/Media/Geometry/Geometry.h"


namespace sw {
namespace gui
{



/**@brief Mock geometry for tests.*/
class FakeGeometry : public Geometry
{
private:
protected:

	std::wstring			m_geomName;

public:
	explicit		FakeGeometry		( bool sharedBuffer );
	virtual			~FakeGeometry		() = default;


public:

	virtual bool			HitTest			( const Point& point ) override;
	virtual bool			HitTest			( const Rect& rectangle ) override;

	virtual GeometryData	Generate		() override;
	virtual BufferRange		BufferData		() override;

	virtual std::wstring	ShaderFunctionFile	() override;
	virtual std::wstring	GeometryName		() override;
	virtual std::wstring	ConstantsName		() override;

public:

	using Geometry::NeedsShaderUpdate;
	using Geometry::NeedsConstantsUpdate;
	using Geometry::NeedsGeometryUpdate;

	void					ChangeGeometry		( const std::wstring& geomName );
};

DEFINE_PTR_TYPE( FakeGeometry )



}	// gui
}	// sw


