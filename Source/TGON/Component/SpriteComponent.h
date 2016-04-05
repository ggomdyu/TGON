#pragma once
#include "IComponent.h"

// Using D3d for a moment
//#include "D3d92DSprite.h"

namespace tgon
{


class SpriteComponent : public IComponent
{
public:
	SpriteComponent( const wchar_t* texturePath );
	~SpriteComponent( );

	void Render( );

private:
	//D3d92DSprite m_texture;
};


}