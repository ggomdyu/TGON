#pragma once
#include "FBXLoader.h"

class CLoadManager
{
private:
	CFBXLoader* m_pFBXLoader;
	LPSTR m_strFileFormat;


public:
	CLoadManager( void );
	~CLoadManager( void );

public:
	HRESULT LoadModel( LPSTR FilePath, LPSTR FileFormat );
	void SetUpVertexData( );
	void Release( );
};

