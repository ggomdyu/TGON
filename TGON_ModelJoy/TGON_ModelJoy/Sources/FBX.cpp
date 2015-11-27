#include "stdafx.h"
#include "FBX.h"

FBX::FBXProxy::FBXProxy( ) :
	m_pFbxManager( FbxManager::Create( )),
	m_pFbxIOSettings( FbxIOSettings::Create( m_pFbxManager, IOSROOT ))
{
	if ( !m_pFbxManager )
	{
		msg::out << "Failed to call FbxIOSettings::Create function.\n\n" << __FILE__ << " (" << __LINE__ << ")" << msg::warn;
		abort( );
	}
	if ( !m_pFbxIOSettings )
	{
		msg::out << "Failed to call FbxIOSettings::Create function.\n\n" << __FILE__ << " (" << __LINE__ << ")" << msg::warn;
		abort( );
	}

	m_pFbxManager->SetIOSettings( m_pFbxIOSettings );
}

FBX::FBXProxy::~FBXProxy( )
{
}

void FBX::FBXProxy::ImportFBX( const char* const szFilePath, FbxScene* const pScene )
{
	FbxImporter* const pImporter( FbxImporter::Create( FBXProxy::get( )->GetManager( ), "" ));
	assert( pImporter != nullptr );

	if ( !pImporter->Initialize( szFilePath )) {
		msg::out << "Failed to call FBXImporter::Initialize function. ( " << szFilePath << " )" << msg::warn;
		abort( );
	}

	if ( !pImporter->Import( pScene )) {
		msg::out << "Failed to call FBXImporter::Import function.\n\n" << __FILE__ << " (" << __LINE__ << ")" << msg::warn;
		abort( );
	}
}

void FBX::LoadAttributes( const char* const szFilePath, FbxScene* const pScene, FbxMesh*& pMesh )
{
	FBXProxy::get( )->ImportFBX( szFilePath, pScene );


	// Get root node of FBX
	FbxNode* const pRootNode = pScene->GetRootNode( );
	FbxNode* pChildNode = nullptr;
	assert( pRootNode != nullptr );

	// Search each other child's hierarchy.
	for ( int nChildCount =0; nChildCount <pRootNode->GetChildCount( ); ++nChildCount )
	{
		pChildNode = pRootNode->GetChild( nChildCount );
		assert( pChildNode != nullptr );

		if ( pChildNode->GetNodeAttribute( ))
		{
			switch ( pChildNode->GetNodeAttribute( )->GetAttributeType( ))
			{
			case FbxNodeAttribute::eMesh:
				pMesh = static_cast<FbxMesh*>( pChildNode->GetNodeAttribute( ));
				break;

			//case FbxNodeAttribute::eLight:
			//	break;

			//case FbxNodeAttribute::eCamera:
			//	break;
			}
		}
	}
}