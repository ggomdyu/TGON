#pragma once

namespace tgon
{


class ModelScene : public IScene
{
public:
	virtual void Update( float tickTime ) override;
	virtual void Render( ) override;

public:
	ModelScene( );
	virtual ~ModelScene( );

};


}