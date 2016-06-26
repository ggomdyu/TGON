/*
* Author : Junho-Cha
* Date : 03/06/2015
* Latest author :
* Latest date :
*/

#pragma once

class IScene
{
public:
	IScene( ) {};
	virtual ~IScene( ) = 0 {};

	virtual void Update( float tickTime ) = 0;
	virtual void Render( ) = 0;
};