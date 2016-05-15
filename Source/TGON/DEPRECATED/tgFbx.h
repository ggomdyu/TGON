/*
* 작성자 : 차준호
* 작성일 : 2015-11-12
* 최종 수정 : 차준호
* 최종 수정일 : 2016-02-01
*/

#pragma once
#include <fbxsdk.h>
#include <memory>

namespace tgon
{
	namespace fbx
	{
		typedef std::shared_ptr<FbxManager>		SpFbxManager;
		typedef std::shared_ptr<FbxIOSettings>		SpFbxIOSettings;


		inline const SpFbxManager&		GetFbxManager( )
		{
			static SpFbxManager fbxManager(
								FbxManager::Create( ), 			
								[]( FbxManager* p ){ p->Destroy( ); }
							);

			return fbxManager;
		}


		inline const SpFbxIOSettings&		GetFbxIOSettings( )
		{
			// This proxy class helps SpFbxIOSettings's initialization.
			struct FbxIOSettingsProxy {
				FbxIOSettingsProxy( ) : m_fbxIOSettings(
								FbxIOSettings::Create( GetFbxManager( ).get( ), IOSROOT ),	
								[]( FbxIOSettings* p ){ p->Destroy( ); }
							) {}

				SpFbxIOSettings m_fbxIOSettings;
			};

			static FbxIOSettingsProxy fbxIOSettingsProxy;
			return fbxIOSettingsProxy.m_fbxIOSettings;
		}
	}
}