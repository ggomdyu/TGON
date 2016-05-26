/*
* Author : Junho-Cha
* Date : 04/26/2015
* Latest author :
* Latest date :
*/


#pragma once
#include "IComponent.h"


namespace tgon
{

class SpriteComponent : public IComponent
{
	/*
		Cons/Destuctor
	*/
public:
	explicit SpriteComponent( const wchar_t* texturePath );
	~SpriteComponent( );


	virtual void Update( float tickTime ) override;
	void Render( );
};


}