#pragma once
/*
* �ۼ��� : ����ȣ
* �ۼ��� : 2015-11-12
* ���� ���� :
* ���� ������ :
*/


class IModelBase
{
public:
	IModelBase( );
	~IModelBase( );

	virtual void Render( ) = 0;

public:
	virtual void LoadMesh( const char* const szFilePath ) = 0;
};