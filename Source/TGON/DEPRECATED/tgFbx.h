/*
* �ۼ��� : ����ȣ
* �ۼ��� : 2015-11-12
* ���� ���� : ����ȣ
* ���� ������ : 2016-02-01
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