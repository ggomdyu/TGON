#include "FBXLoader.h"


CFBXLoader::CFBXLoader( void )
{
	m_pFBXManager = nullptr;
	m_pFBXScene = nullptr;
}


CFBXLoader::~CFBXLoader( void )
{
	Release( );
}

HRESULT CFBXLoader::LoadFBX( LPSTR FilePath )
{
	if ( !FilePath )
		return E_FAIL;

	HRESULT hr = S_OK;

	InitializeFBXSDKObjects( m_pFBXManager, m_pFBXScene );

	if ( !m_pFBXManager )
		return E_FAIL;


	int iFileFormat = -1;
	m_pFBXImporter = FbxImporter::Create( m_pFBXManager, "" );

	if ( !( m_pFBXManager->GetIOPluginRegistry( )->DetectReaderFileFormat( FilePath, iFileFormat ) ) )
	{
		iFileFormat = m_pFBXManager->GetIOPluginRegistry( )->FindReaderIDByDescription( "FBX binary (*.fbx)" );
	}

	if ( ( !( m_pFBXImporter ) ) || ( m_pFBXImporter->Initialize( FilePath, iFileFormat ) == false ) )
		return E_FAIL;

	if ( ( !( m_pFBXImporter ) ) || ( m_pFBXImporter->Import( m_pFBXScene ) == false ) )
		return E_FAIL;

	/*FbxSystemUnit SceneSystemUnit = m_pFBXScene->GetGlobalSettings( ).GetSystemUnit( );

	if ( SceneSystemUnit.GetScaleFactor( ) != 1.0 )
	{
		FbxSystemUnit::cm.ConvertScene( m_pFBXScene );
	}*/

	TriangulateRecursive( m_pFBXScene->GetRootNode( ) );

	SetUp( );

	return S_OK;
}

void CFBXLoader::InitializeFBXSDKObjects( FbxManager*& pFBXManager, FbxScene*& pFBXScene )
{
	pFBXManager = FbxManager::Create( );

	if ( !pFBXManager )
	{
		FBXSDK_printf( "Error! : Failed to Create FBX Manager!!!\n" );
		exit( 1 );
	}

	FbxIOSettings* pIOSettings = FbxIOSettings::Create( pFBXManager, IOSROOT );

	pFBXManager->SetIOSettings( pIOSettings );

	FbxString fbxStrPath = FbxGetApplicationDirectory( );
	pFBXManager->LoadPluginsDirectory( fbxStrPath.Buffer( ) );

	pFBXScene = FbxScene::Create( pFBXManager, "ModelJoy_FBX_Scene" );

	if ( !pFBXScene )
	{
		FBXSDK_printf( "Error: Failed to create FBX Scene!!!\n" );
		exit( 1 );
	}
}

void CFBXLoader::TriangulateRecursive( FbxNode* pNode )
{
	FbxNodeAttribute* pFBXNodeAttribute = pNode->GetNodeAttribute( );

	if ( pFBXNodeAttribute )
	{
		if ( pFBXNodeAttribute->GetAttributeType( ) == FbxNodeAttribute::eMesh ||
			 pFBXNodeAttribute->GetAttributeType( ) == FbxNodeAttribute::eNurbs ||
			 pFBXNodeAttribute->GetAttributeType( ) == FbxNodeAttribute::eNurbsSurface ||
			 pFBXNodeAttribute->GetAttributeType( ) == FbxNodeAttribute::ePatch )
		{
			FbxGeometryConverter FBX_G_Converter( pNode->GetFbxManager( ) );

			FBX_G_Converter.Triangulate( m_pFBXScene, true );
		}
	}

	const int iChildCount = pNode->GetChildCount( );

	for ( int iChildIndex = 0; iChildIndex < iChildCount; iChildIndex++ )
	{
		TriangulateRecursive( pNode->GetChild( iChildIndex ) );
	}
}

FbxNode& CFBXLoader::GetRootNode( )
{
	return *m_pFBXScene->GetRootNode( );
}

void CFBXLoader::SetUp( )
{
	if ( m_pFBXScene->GetRootNode( ) )
	{
		SetUpNode( m_pFBXScene->GetRootNode( ), "NULL" );
	}
}

void CFBXLoader::SetUpNode( FbxNode* pNode, std::string parentNodeName )
{
	if ( !pNode )
		return;

	FBX_MESH_NODE meshNode;

	meshNode.m_MESH_NODE_NAME = pNode->GetName( );
	meshNode.m_MESH_PARANT_NODE_NAME = parentNodeName;

	ZeroMemory( &meshNode.m_ELEMENTS, sizeof( MESH_ELEMENTS ) );

	FbxMesh* pFBXMesh = pNode->GetMesh( );

	if ( pFBXMesh )
	{
		const int iVertexCount = pFBXMesh->GetControlPointsCount( );

		if ( iVertexCount > 0 )
		{
			CopyVertexData( pFBXMesh, &meshNode );
		}
	}

	ComputeNodeMatrix( pNode, &meshNode );

	m_MeshNodes.push_back( meshNode );

	const int iChildCount = pNode->GetChildCount( );

	for ( int iChildIndex = 0; iChildIndex < iChildCount; iChildIndex++ )
	{
		SetUpNode( pNode->GetChild( iChildIndex ), meshNode.m_MESH_NODE_NAME );
	}
}

void CFBXLoader::ComputeNodeMatrix( FbxNode* pNode, FBX_MESH_NODE* meshNode )
{
	if ( ( !( pNode ) ) || ( !( meshNode ) ) )
		return;

	FbxAnimEvaluator* pFBXEvaluator = m_pFBXScene->GetAnimationEvaluator( );
	FbxMatrix pFBXmat_Global;

	pFBXmat_Global.SetIdentity( );

	if ( pNode != m_pFBXScene->GetRootNode( ) )
	{
		pFBXmat_Global = pFBXEvaluator->GetNodeGlobalTransform( pNode );

		FBXMatrixToFloat16( &pFBXmat_Global, meshNode->MATRIX4x4 );
	}
	else
	{
		FBXMatrixToFloat16( &pFBXmat_Global, meshNode->MATRIX4x4 );
	}
}

void CFBXLoader::CopyVertexData( FbxMesh* pMesh, FBX_MESH_NODE* meshNode )
{
	if ( !pMesh )
		return;

	int iPolygonCount = pMesh->GetPolygonCount( );

	FbxVector4 fvPos, fvNor;

	meshNode->m_ELEMENTS.m_POSITION = 1;
	meshNode->m_ELEMENTS.m_NORMAL = 1;

	unsigned int iIndex = 0;

	for ( int i = 0; i < iPolygonCount; i++ )
	{
		int iPolygonSize = pMesh->GetPolygonSize( i );

		for ( int pol = 0; pol < iPolygonSize; pol++ )
		{
			int Index = pMesh->GetPolygonVertex( i, pol );
			meshNode->m_INDEXS.push_back( iIndex );

			fvPos = pMesh->GetControlPointAt( Index );
			pMesh->GetPolygonVertexNormal( i, pol, fvNor );

			meshNode->m_POSITIONS.push_back( fvPos );
			meshNode->m_NORMALS.push_back( fvNor );

			CUSTOMVERTEX* pVertices = new CUSTOMVERTEX;

			pVertices->m_fX = static_cast< float >( fvPos.mData[ 0 ] );
			pVertices->m_fY = static_cast< float >( fvPos.mData[ 1 ] );
			pVertices->m_fZ = static_cast< float >( fvPos.mData[ 2 ] );

			/*pVertices->m_fX = static_cast< float >( fvNor.mData[ 0 ] );
			pVertices->m_fY = static_cast< float >( fvNor.mData[ 1 ] );
			pVertices->m_fZ = static_cast< float >( fvNor.mData[ 2 ] );*/

			pVertices->m_fRHW = 1.0f;
			pVertices->m_dwColor = 0xff00ff00;

			Direct3D( )->GetVertexVector( )->push_back( pVertices );

			++iIndex;
		}
	}
}

FBX_MESH_NODE& CFBXLoader::GetNode( const unsigned int Index )
{
	return m_MeshNodes[ Index ];
}

void CFBXLoader::Release( )
{
	for ( auto MESH_NODE : m_MeshNodes )
	{
		MESH_NODE.Release( );
	}

	m_MeshNodes.clear( );

	if ( m_pFBXImporter != nullptr )
	{
		m_pFBXImporter->Destroy( );
		m_pFBXImporter = nullptr;
	}

	if ( m_pFBXScene != nullptr )
	{
		m_pFBXScene->Destroy( );
		m_pFBXScene = nullptr;
	}

	if ( m_pFBXManager != nullptr )
	{
		m_pFBXManager->Destroy( );
		m_pFBXManager = nullptr;
	}
}
