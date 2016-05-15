/*
* Author : Junho-Cha
* Date : 05/10/2016
* Latest author :
* Latest date :
*/

#pragma once
#include "../Scene/IScene.h"

class DefaultScene : public IScene
{
public:
	virtual void Update( float tickTime ) override;
	virtual void Render( ) override;

public:
	DefaultScene( ) {}
	virtual ~DefaultScene( ) {}
};