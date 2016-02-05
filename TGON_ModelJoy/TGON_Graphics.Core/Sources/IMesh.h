/*
* 작성자 : 차준호
* 작성일 : 2015-11-12
* 최종 수정 :
* 최종 수정일 :
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