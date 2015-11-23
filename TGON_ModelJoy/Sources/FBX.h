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
	struct FBXProxy final : CSingleton<FBXProxy>
	{
	public:
		FBXProxy( );
		~FBXProxy( );

		__forceinline static void ImportFBX( _In_ const char* const szFilePath, _Out_ FbxScene* const pScene );
		__forceinline FbxManager* GetManager( ) const { return m_pFbxManager; }

	private:
		FbxManager* m_pFbxManager;
		FbxIOSettings* m_pFbxIOSettings;
	};

public:
	static void LoadAttributes( _In_ const char* const szFilePath, _Out_ FbxScene* const pScene,
										_Out_ FbxMesh*& pMesh );

	__forceinline static FbxManager* GetManager( ) { return FBXProxy::get( )->GetManager( ); }

private:
	FBX( ) = delete;
	~FBX( ) = delete;
};

