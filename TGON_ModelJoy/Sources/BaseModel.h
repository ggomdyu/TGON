#pragma once
/*
* �ۼ��� : ����ȣ
* �ۼ��� : 2015-11-12
* ���� ���� :
* ���� ������ :
*/


class BaseModel
{
public:
	BaseModel( );
	~BaseModel( );

	virtual void Render( ) = 0;

public:
	virtual bool LoadMesh( const char* const szFilePath ) = 0;
};