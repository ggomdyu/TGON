#pragma once
#include <Scene/IScene.h>

namespace tgon
{


class ModelScene : public IScene
{
public:
	ModelScene( );
	virtual ~ModelScene( );

	virtual void Tick( float tickTime ) override;
	virtual void Render( ) override;

public:
};


}