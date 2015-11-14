#include "stdafx.h"
#include "FBX.h"

FBX::FBXProxy::FBXProxy( ) :
	m_pFbxManager( FbxManager::Create( )),
	m_pFbxIOSettings( FbxIOSettings::Create( m_pFbxManager, IOSROOT ))
{
	if ( !m_pFbxManager )
	{
		msg::out << "Failed to call FbxIOSettings::Create function." << msg::warn;
		abort( );
	}
	if ( !m_pFbxIOSettings )
	{
		msg::out << "Failed to call FbxIOSettings::Create function." << msg::warn;
		abort( );
	}

	m_pFbxManager->SetIOSettings( m_pFbxIOSettings );
}

FBX::FBXProxy::~FBXProxy( )
{
}

void FBX::LoadAttributes( const char* const szFilePath, const FbxScene* const pCurScene, FbxMesh*& pNewMesh )
{
	// Get root node of FBX
	FbxNode* const pRootNode = pCurScene->GetRootNode( );
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
				pNewMesh = static_cast<FbxMesh*>( pChildNode->GetNodeAttribute( ));
				break;

			//case FbxNodeAttribute::eLight:
			//	break;

			//case FbxNodeAttribute::eCamera:
			//	break;
			}
		}
	}
}