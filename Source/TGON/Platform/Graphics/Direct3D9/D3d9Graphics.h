/*
* Author : Taewoo-Kim
* Date : 04/26/2015
* Latest author : Junho-Cha
* Latest date : 01/17/2016
*/


#pragma once
#include "../Abstract/AbstractGraphics.h"
#include "../../Config/Build.h"

#include <d3d9.h>
#include "D3d9Type.h"

#pragma comment( lib, "d3d9.lib" )

#if defined( _DEBUG ) || defined( DEBUG )
#	pragma comment( lib, "d3dx9d.lib" )
#else
#	pragma comment( lib, "d3dx9.lib" )
#endif


namespace tgon
{


class TGON_API D3d9Graphics : 
	private AbstractGraphics
{
public:
	explicit D3d9Graphics( );
	virtual ~D3d9Graphics( );

public:
	const SpD3d9Ex& GetD3d( ) const;
	
private:
	void InitInterface( );

private:
	SpD3d9Ex m_d3d;
};

using GraphicsImpl = D3d9Graphics;
using SpTGraphics = std::shared_ptr<GraphicsImpl>;
using WpTGraphics = std::weak_ptr<GraphicsImpl>;


inline const SpD3d9Ex& D3d9Graphics::GetD3d( ) const
{
	return m_d3d;
}


}