/*
* �ۼ��� : ����ȣ
* �ۼ��� : 2015-11-12
* ���� ���� :
* ���� ������ :
*/

#pragma once


class IMesh
{
public:
	IMesh( );
	~IMesh( );

	virtual void LoadX( const char* szFilePath )			{};
	virtual void LoadFBX( const char* szFilePath )		{};


	virtual void BeginDisplay( ) = 0;
	virtual void EndDisplay( ) = 0;

public:
};