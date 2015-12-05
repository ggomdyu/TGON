#include "stdafx.h"
#include "FBX.h"

FBX::FBX( ) :
	m_fbxManager( FbxManager::Create( )),
	m_fbxIOSettings( FbxIOSettings::Create( m_fbxManager, IOSROOT ))
{
	if ( !m_fbxManager )
	{
		msg::out << "Failed to call FbxManager::Create function.\n\n" << __FILE__ << " (" << __LINE__ << ")" << msg::warn;
		abort( );
	}

	if ( !m_fbxIOSettings )
	{
		msg::out << "Failed to call FbxIOSettings::Create function.\n\n" << __FILE__ << " (" << __LINE__ << ")" << msg::warn;
		abort( );
	}

	m_fbxManager->SetIOSettings( m_fbxIOSettings );
}

FBX::~FBX( )
{
}




FBXImporter::FBXImporter( _In_ const char* fbxFilepath ) :
	m_fbxImporter( FbxImporter::Create( FBX::GetInstance( )->GetFbxManager( ), "" ))
{
	if ( !m_fbxImporter )
	{
		msg::out << "Failed to call FBXImporter::Create function.\n\n" << __FILE__ << " (" << __LINE__ << ")" << msg::warn;
		abort( );
	}

	if ( fbxFilepath )
	{
		ReadFBX( fbxFilepath );
	}
}

FBXImporter::~FBXImporter( )
{
}

void FBXImporter::ReadFBX( _In_ const char* fbxFilepath )
{
	LoadScene( fbxFilepath ); /* FBXScene has all nodes: Mesh, ... */
	ProcessScene( );
}

void FBXImporter::LoadScene( _In_ const char* fbxFilepath )
{
	if ( !m_fbxImporter->Import( m_fbxScene )) {
		msg::out << "Failed to call FBXImporter::Import function.\n\n" << __FILE__ << " (" << __LINE__ << ")" << msg::warn;
		abort( );
	}
}

void FBXImporter::ProcessScene( int poseIndex )
{
	FbxNode* rootNode = m_fbxScene->GetRootNode( );
	FbxPose* pose = nullptr;

	/*
		- What is the FbxPose?

		TODO: describe that
	*/
	if ( poseIndex >= 0 )
		pose = m_fbxScene->GetPose( poseIndex );

	/*int materialArrayCount = pScene->GetMaterialCount();

	for(int i = 0; i < materialArrayCount; i++)
	{
		FbxSurfaceMaterial* pMaterial =  pScene->GetMaterial(i);
		std::string name = pMaterial->GetName();
		int t = 1;
	}*/

	ProcessNodeRecursive( rootNode, pose, m_fbxRootFrame );
	m_fbxRootFrame->frameType = FrameEnum::Root;
}

void FBXImporter::ProcessNodeRecursive( FbxNode* fbxNode, FbxPose* fbxPose, FbxFrame* fbxFrame )
{
	ProcessNode( fbxNode, fbxPose, fbxFrame );

	//FbxFrame* childFrame = fbxFrame->pFrameFirstChild;

	int childCount = fbxNode->GetChildCount( );
	for ( int i = 0; i < childCount; i++ )
	{
		ProcessNodeRecursive( fbxNode->GetChild( i ), fbxPose, childFrame );
	//	childFrame = childFrame->pFrameSibling;
	}
}

void FBXImporter::ProcessNode( FbxNode* fbxNode, FbxPose* fbxPose, FbxFrame* fbxFrame )
{
	SetNodeProperties( fbxNode, fbxPose, fbxFrame );

	FbxNodeAttribute* nodeAttribute = fbxNode->GetNodeAttribute( );
	FbxNodeAttribute::EType attributeType = FbxNodeAttribute::eNull;

	if ( nodeAttribute )
		attributeType = nodeAttribute->GetAttributeType( );


	switch ( attributeType )
	{
	case FbxNodeAttribute::eMarker:
		//ProcessMarkerNode( pNode, pPose, pFrame );
		break;

	case FbxNodeAttribute::eSkeleton:
		//ProcessSkeletonNode( pNode, pPose, pFrame );
		break;

	case FbxNodeAttribute::eMesh:
		ProcessMeshNode( fbxNode, fbxPose, fbxFrame );
		break;

	case FbxNodeAttribute::eNurbs:
		// Not supported yet. 
		// Should have been converted into a mesh in function ConvertNurbsAndPatch().
		assert( 0 );
		break;

	case FbxNodeAttribute::ePatch:
		// Not supported yet. 
		// Should have been converted into a mesh in function ConvertNurbsAndPatch().
		break;

	case FbxNodeAttribute::eCamera:
		//ProcessCameraNode( pNode, pPose, pFrame );
		break;

	case FbxNodeAttribute::eLight:
		//ProcessLightNode( pNode, pPose, pFrame );
		break;

	case FbxNodeAttribute::eNull:
	default:
		fbxFrame->frameType = FrameEnum::Null;
		break;
	}
}

void FBXImporter::SetNodeProperties( FbxNode* fbxNode, FbxPose* pose, FbxFrame* fbxFrame )
{
#if RESET_PIVOT
	pNode->SetDefaultT( pNode->GetLocalTFromCurrentTake( 0, false ));
	pNode->SetDefaultR( pNode->GetLocalRFromCurrentTake( 0, false ));
	pNode->SetDefaultS( pNode->GetLocalSFromCurrentTake( 0, false ));
#endif

	std::string nodeName = fbxNode->GetName( );

	//Set the node pointer for light and camera handling.
	fbxFrame->name = nodeName;

	FbxTransform::EInheritType inheritType;
	fbxNode->GetTransformationInheritType( inheritType );

	FbxNode* nodeParent = fbxNode->GetParent( );
	if ( nodeParent )
	{
		FbxTransform::EInheritType etitParent;

		// if the parent inherit type is "None"   (eINHERIT_Rrs), then the child behaves as 
		// if its inherit type was none.

		nodeParent->GetTransformationInheritType( etitParent );
		if ( etitParent == FbxTransform::eInheritRrs )
		{
			inheritType = FbxTransform::eInheritRrs;
		}
	}
	FbxAMatrix orientedPosition = GetLocalTransform( pNode );

	MatrixConvert( orientedPosition, fbxFrame->transformationMatrix );



	switch ( inheritType )
	{
	case FbxTransform::eInheritRrSs:
		fbxFrame->inheritanceType = kINHERIT_RrSs;
		break;

	case FbxTransform::eInheritRSrs:
		fbxFrame->inheritanceType = kINHERIT_RSrs;
		break;

	case FbxTransform::eInheritRrs:
		fbxFrame->inheritanceType = kINHERIT_Rrs;
		break;
	}
}

void FBXImporter::ProcessMeshNode( FbxNode* fbxNode, FbxPose* fbxPose, FbxFrame* fbxFrame )
{
	const char* nodeName = fbxNode->GetName( );

	fbxFrame->frameType = FrameEnum::Mesh;
	if ( !fbxNode->GetVisibility( ))
		return;

	FbxMesh* fbxMesh = static_cast<FbxMesh*>( fbxNode->GetNodeAttribute( ));

	// No verts.
	int vertexCount = fbxMesh->GetControlPointsCount( );
	if ( vertexCount == 0 )
	{
		return;
	}

	bool needToTriangulate = false;
	int polyCount = fbxMesh->GetPolygonCount( );
	for ( int polyIndex = 0; polyIndex <polyCount; polyIndex++ )
	{
		int polySize = fbxMesh->GetPolygonSize( polyIndex );

		if ( polySize > 3 )
		{
			needToTriangulate = true;
			break;
		}

	}

	if ( needToTriangulate )
	{
		// Not support currently
		/*FbxGeometryConverter geometryConverter( FBX::GetInstance( )->GetFbxManager( ));
		geometryConverter.TriangulateInPlace( pNode );

		pMesh = ( FbxMesh* )pNode->GetNodeAttribute( );*/
	}


	CreateMeshObject( pFrame, pNode, m_nodeToFrameMap );
}

bool FBXImporter::CreateMeshObject( FbxFrame* fbxFrame, FbxNode* fbxNode/*, NodeToFrameMap & nodeToFrameMap*/)
{
	char str[MAX_PATH] = { 0 };

	// Start clean

	//	ClearPerMesh();

	// to map control points to split verts
	//	ControlPointRemap controlPointRemap;
	m_fbxScene->getnodelocal
	FbxVector4 scaling = fbxNode->GetScene()->GetEvaluator()->GetNodeLocalScaling(fbxNode);


	std::shared_ptr<FbxMesh> mesh;
	//bool bSuccess =  GetScene()->CreateMesh(spMesh );
	mesh.reset(new lpFBXMesh, deleter<lpFBXMesh>());


	mesh->m_negativeScales = 0;
	if (scaling[0] < 0)
	mesh->m_negativeScales++;
	if (scaling[1] < 0)
	mesh->m_negativeScales++;
	if (scaling[2] < 0)
	mesh->m_negativeScales++;


	LoadGeometryFromNode(mesh, fbxNode, fbxFrame, controlPointRemap) ;
	LoadMaterialsFromNode(mesh, fbxNode) ;


	// Set the current directory based on where the mesh was found
	char wstrOldDir[MAX_PATH] = {0};
	GetCurrentDirectoryA( MAX_PATH, wstrOldDir );
	SetCurrentDirectoryA( m_strMediaDir.c_str());


	// Restore the original current directory
	SetCurrentDirectoryA( wstrOldDir );


	// Create the mesh
	

	//assert(bSuccess);



	//int numSkinVerts = mesh->GetNumVertices();

	//lpVertexSkinning * pSkinInfo = 0;
	//CreateBoneStructure(
	//	fbxNode, pSkinInfo, 
	//	numSkinVerts,
	//	controlPointRemap,
	//   nodeToFrameMap);

	////spMesh->GenerateAdjacency() ;


	//// create mesh container in the frame
	//std::string nodeName = fbxNode->GetName();

	//GetScene()->CreateMeshContainer(nodeName.c_str(), 
	//	mesh, 
	//	pSkinInfo,
	//	fbxFrame->pMeshContainer);




	//FbxMesh* pFBXMesh = (FbxMesh*) fbxNode->GetNodeAttribute();
	//int lPolygonCount = pFBXMesh->GetPolygonCount();

	//int nPoints;
	//if (controlPointRemap.size())
	//	nPoints = lPolygonCount * 3;     
	//else
	//	nPoints = pFBXMesh->GetControlPointsCount();   



	return true;
}

void FBXImporter::ProcessLightNode( )
{
}

void FBXImporter::ProcessCameraNode( )
{
}