#pragma once
/*
* 작성자 : 차준호
* 작성일 : 2015-11-12
* 최종 수정 :
* 최종 수정일 :
*/

#ifndef TGON_USE_PRECOMPILED_HEADER
	#include <fbxsdk.h>
	#include "Singleton.h"
	#include "msgstream.h"
#endif

class FBX final
{
private:
	struct FBXProxy : CSingleton<FBXProxy>
	{
	public:
		FBXProxy( );
		~FBXProxy( );

		__forceinline FbxManager* GetFbxManager( ) const { return m_pFbxManager; }

	private:
		FbxManager* m_pFbxManager;
		FbxIOSettings* m_pFbxIOSettings;
	};

public:
	static void ImfortFBX( _In_ const char* const szFilePath, _In_ FbxScene* const pScene );

	static void LoadAttributes( _In_ const char* const szFilePath, _In_ const FbxScene* const pScene,
										_Out_ FbxMesh*& pMesh );

public:
	__forceinline static FbxManager* GetManager( ) { return FBXProxy::get( )->GetFbxManager( ); }

private:
	FBX( ) = delete;
	~FBX( ) = delete;
};

