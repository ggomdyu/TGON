/*
* 작성자 : 차준호
* 작성일 : 2015-03-06
* 최종 수정 :
* 최종 수정일 :
*/

#pragma once

class IScene
{
public:
	IScene( ) {};
	virtual ~IScene( ) = 0 {};

	virtual void Tick( float tickTime ) = 0;
	virtual void Render( ) = 0;
};