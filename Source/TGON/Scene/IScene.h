/*
* �ۼ��� : ����ȣ
* �ۼ��� : 2015-03-06
* ���� ���� :
* ���� ������ :
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