#pragma once
#include "Singleton.h"
#include "Direct3D.h"
#include "LoadManager.h"


class CToolManager : public CSingleton<CToolManager>
{
private:
	CLoadManager* m_pLoadMgr;

public:
	CToolManager( void );
	~CToolManager( void );

	HRESULT TOOLINIT( HWND hWnd, bool isWindow );
	void TOOLUNINIT( );
	void Update( );
	void InputUpdate( );
	void Render( );

public:
	inline CLoadManager* GetLoadMgr( ) { return m_pLoadMgr; }
};
#define ToolMgr() CSingleton<CToolManager>::InstancePtr()

