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
		this->ReadFBX( fbxFilepath );
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

	FbxFrame* childFrame = fbxFrame->frameFirstChild;

	int childCount = fbxNode->GetChildCount( );
	for ( int i = 0; i < childCount; i++ )
	{
		ProcessNodeRecursive( fbxNode->GetChild( i ), fbxPose, childFrame );
		childFrame = childFrame->frameSibling;
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
//#if RESET_PIVOT
//	pNode->SetDefaultT( pNode->GetLocalTFromCurrentTake( 0, false ));
//	pNode->SetDefaultR( pNode->GetLocalRFromCurrentTake( 0, false ));
//	pNode->SetDefaultS( pNode->GetLocalSFromCurrentTake( 0, false ));
//#endif
//
//	std::string nodeName = fbxNode->GetName( );
//
//	//Set the node pointer for light and camera handling.
//	fbxFrame->name = nodeName;
//
//	FbxTransform::EInheritType inheritType;
//	fbxNode->GetTransformationInheritType( inheritType );
//
//	FbxNode* nodeParent = fbxNode->GetParent( );
//	if ( nodeParent )
//	{
//		FbxTransform::EInheritType etitParent;
//
//		// if the parent inherit type is "None"   (eINHERIT_Rrs), then the child behaves as 
//		// if its inherit type was none.
//
//		nodeParent->GetTransformationInheritType( etitParent );
//		if ( etitParent == FbxTransform::eInheritRrs )
//		{
//			inheritType = FbxTransform::eInheritRrs;
//		}
//	}
//	FbxAMatrix orientedPosition = GetLocalTransform( pNode );
//
//	MatrixConvert( orientedPosition, fbxFrame->transformationMatrix );
//
//
//
//	switch ( inheritType )
//	{
//	case FbxTransform::eInheritRrSs:
//		fbxFrame->inheritanceType = kINHERIT_RrSs;
//		break;
//
//	case FbxTransform::eInheritRSrs:
//		fbxFrame->inheritanceType = kINHERIT_RSrs;
//		break;
//
//	case FbxTransform::eInheritRrs:
//		fbxFrame->inheritanceType = kINHERIT_Rrs;
//		break;
//	}
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


	CreateMeshObject( fbxFrame, fbxNode/*, m_nodeToFrameMap*/ );
}

bool FBXImporter::CreateMeshObject( FbxFrame* fbxFrame, FbxNode* fbxNode/*, NodeToFrameMap & nodeToFrameMap*/)
{
	char str[MAX_PATH] = { 0 };

	// Start clean

	//	ClearPerMesh();

	// to map control points to split verts
	ControlPointRemap controlPointRemap;
	//FbxVector4 scaling = fbxNode->GetScene()->GetEvaluator()->GetNodeLocalScaling(fbxNode);


	//std::shared_ptr<lpFbxMesh> mesh;


	//mesh->m_negativeScales = 0;
	//if (scaling[0] < 0)
	//mesh->m_negativeScales++;
	//if (scaling[1] < 0)
	//mesh->m_negativeScales++;
	//if (scaling[2] < 0)
	//mesh->m_negativeScales++;


	LoadGeometryFromNode(/*mesh, */fbxNode, fbxFrame, controlPointRemap) ;
	//LoadMaterialsFromNode(mesh, fbxNode) ;


	//// Set the current directory based on where the mesh was found
	//char wstrOldDir[MAX_PATH] = {0};
	//GetCurrentDirectoryA( MAX_PATH, wstrOldDir );
	//SetCurrentDirectoryA( m_strMediaDir.c_str());

	//
	//// Restore the original current directory
	//SetCurrentDirectoryA( wstrOldDir );


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

void FBXImporter::LoadGeometryFromNode( /*spFBXMesh& spMesh,*/ FbxNode* fbxNode, FbxFrame* fbxFrame,
			ControlPointRemap& controlPointRemap )
{
	const char* name = fbxNode->GetName( );

	// The first subset uses the default material
	FbxMesh* fbxMesh = static_cast<FbxMesh*>( fbxNode->GetNodeAttribute( ));


	const int controlPointsCount = fbxMesh->GetControlPointsCount( );
	FbxVector4* controlPoints = fbxMesh->GetControlPoints( );

	/*
		scan attributes
	*/
	const int polyCount = fbxMesh->GetPolygonCount( );
	//spMesh->m_attributeList.resize( polyCount );

	for ( int i = 0; i < polyCount; i++ )
	{
		// default is default material
		//spMesh->m_attributeList[i] = 0;
	}

	/*
		Exception filter??
	*/
	for ( int polyIndex = 0; polyIndex < polyCount; ++polyIndex )
	{
		int startIndex = fbxMesh->GetPolygonVertexIndex( polyIndex );
		if ( startIndex == -1 )
			continue;

		int* vertices = &fbxMesh->GetPolygonVertices( )[startIndex];
		int vertexCount = fbxMesh->GetPolygonSize( polyIndex );

		for ( int vertexIndex = 0; vertexIndex < vertexCount; ++vertexIndex )
		{
			int vertexID = vertices[vertexIndex];
			int controlPointIndex = fbxMesh->GetPolygonVertex( polyIndex, vertexIndex );
			assert( vertexID == controlPointIndex );
		}
	}

	// when we split verts, map control points to the split vert location
	controlPointRemap.clear( );



	controlPointRemap.resize( fbxMesh->GetControlPointsCount( ));
	int t = 0;
	for ( int polyIndex = 0; polyIndex < polyCount; polyIndex++ )
	{
		int polySize = fbxMesh->GetPolygonSize( polyIndex );
		assert( polySize == 3 );

		for ( int lVertexIndex = 0; lVertexIndex < polySize; lVertexIndex++ )
		{
			int lControlPointIndex = fbxMesh->GetPolygonVertex( polyIndex, lVertexIndex );

			assert( lControlPointIndex >= 0 );
			assert( t == polyIndex * 3 + lVertexIndex );
			controlPointRemap[lControlPointIndex].insert( polyIndex * 3 + lVertexIndex );
			t++;
		}
	}

	LoadGeometryFromNode( spMesh, fbxNode, controlPointRemap );


	for ( int i = 0; i < fbxMesh->GetLayerCount( ); i++ )
	{

		FbxLayer * pLayer = fbxMesh->GetLayer( i );
		if ( pLayer == NULL )
			continue;

		LoadAttributeIDsFromLayer( spMesh, fbxNode, fbxMesh, pLayer );

	}
}

bool FBXImportExport::LoadGeometryFromNode( spFBXMesh & spMesh, FbxNode* pNode, ControlPointRemap & controlPointRemap )
{


	const char * nodeName = pNode->GetName( );

	// The first subset uses the default material

	FbxMesh* pFBXMesh = ( FbxMesh* )pNode->GetNodeAttribute( );


	int lPolygonCount = pFBXMesh->GetPolygonCount( );
	int lControlPointsCount = pFBXMesh->GetControlPointsCount( );

	lpUnskinnedVertexVector  & unskinnedVertexList = spMesh->m_unskinnedVertexList;


	unskinnedVertexList.resize( lPolygonCount * 3 );


	spMesh->m_bTextureCoordinatesPresent = false;
	spMesh->m_bNormalsPresent = false;

	for ( size_t i = 0; i < unskinnedVertexList.size( ); i++ )
	{
		lpUnskinnedVertex & v = unskinnedVertexList[i];
		v.pos.x = 0;
		v.pos.y = 0;
		v.pos.z = 0;

		v.normal.x = 0;
		v.normal.y = 0;
		v.normal.z = 0;

		v.texcoord.x = 0;
		v.texcoord.y = 0;

	}


	FbxVector4* lControlPoints = pFBXMesh->GetControlPoints( );

	int numControlPoint = pFBXMesh->GetControlPointsCount( );
	FbxVector4 * points = pFBXMesh->GetControlPoints( );


	// m_Indices need to build


	spMesh->m_indexList.resize( lPolygonCount * 3 );

	for ( int i = 0; i < lPolygonCount * 3; i++ )
		spMesh->m_indexList[i] = i;


	FbxAMatrix lReferenceGeometry = GetGeometry( pFBXMesh->GetNode( ) );
	float4x4 geometryMatrix;
	MatrixConvert( lReferenceGeometry, geometryMatrix );



	for ( int lPolygonIndex = 0; lPolygonIndex < lPolygonCount; lPolygonIndex++ )
	{
		int lPolygonSize = pFBXMesh->GetPolygonSize( lPolygonIndex );
		assert( lPolygonSize == 3 );

		for ( int lVertexIndex = 0; lVertexIndex < lPolygonSize; lVertexIndex++ )
		{
			int lControlPointIndex = pFBXMesh->GetPolygonVertex( lPolygonIndex, lVertexIndex );

			FbxVector4 p = lControlPoints[lControlPointIndex];

			int flatIndex = lPolygonIndex * 3 + lVertexIndex;

			lpUnskinnedVertex & v = unskinnedVertexList[flatIndex];

			v.pos.x = p[0];
			v.pos.y = p[1];
			v.pos.z = p[2];

			//float3TransformCoord(&v.pos, &v.pos,  &geometryMatrix);
			v.pos = geometryMatrix * v.pos;
		}
	}


	for ( int l = 0; l < pFBXMesh->GetLayerCount( ); l++ )
	{
		FbxLayerElementNormal* pLayerNormals = pFBXMesh->GetLayer( l )->GetNormals( );
		if ( pLayerNormals == NULL )
			continue;

		FbxLayerElement::EMappingMode normalMappingMode = pLayerNormals->GetMappingMode( );
		FbxLayerElement::EReferenceMode normalReferenceMode = pLayerNormals->GetReferenceMode( );
		if ( normalMappingMode == FbxLayerElement::eByControlPoint )
		{
			for ( int controlPointIndex = 0; controlPointIndex < numControlPoint; controlPointIndex++ )
			{
				FbxVector4 normal = pLayerNormals->GetDirectArray( ).GetAt( controlPointIndex );

				lpUnskinnedVertex * v = 0;
				//if (bSplit)
				{
					unsorted_set<int> & remappedVertexSet = controlPointRemap[controlPointIndex];
					unsorted_set<int>::iterator it;
					FOR_EACH( remappedVertexSet, it )
					{
						int vid = *it;


						lpUnskinnedVertex & v = unskinnedVertexList[vid];

						if ( normal[0] != 0 || normal[1] != 0 || normal[0] != 0 )
							spMesh->m_bNormalsPresent = true;

						v.normal.x = normal[0];
						v.normal.y = normal[1];
						v.normal.z = normal[2];
						//validate(v.normal);
						normalizeInSitu( v.normal );

					}
				}
				/*else
				{

				lpUnskinnedVertex & v =  unskinnedVertexList[controlPointIndex];

				v.normal.x = normal[0];
				v.normal.y = normal[1];
				v.normal.z = normal[2];
				}*/

			}
		}
		else if ( normalMappingMode == FbxLayerElement::eByPolygonVertex )
		{
			switch ( normalReferenceMode )
			{
			case FbxLayerElement::eDirect:
			{
				for ( int i = 0; i < lPolygonCount; i++ )
				{
					int lPolygonSize = pFBXMesh->GetPolygonSize( i );

					for ( int j = 0; j < lPolygonSize; j++ )
					{

						FbxVector4 normal( 0, 0, 0, 0 );
						pFBXMesh->GetPolygonVertexNormal( i, j, normal );


						int lControlPointIndex = pFBXMesh->GetPolygonVertex( i, j );


						lpUnskinnedVertex & v = unskinnedVertexList[i * 3 + j];

						if ( normal[0] != 0 || normal[1] != 0 || normal[0] != 0 )
							spMesh->m_bNormalsPresent = true;

						v.normal.x = normal[0];
						v.normal.y = normal[1];
						v.normal.z = normal[2];
						//validate(v.normal);

						normalizeInSitu( v.normal );


					}
				}


			}
			break;

			case FbxLayerElement::eIndexToDirect:
			{
				for ( int i = 0; i < lPolygonCount; i++ )
				{

					int lPolygonSize = pFBXMesh->GetPolygonSize( i );

					for ( int j = 0; j < lPolygonSize; j++ )
					{
						int lControlPointIndex = pFBXMesh->GetPolygonVertex( i, j );

						FbxVector4 normal( 0, 0, 0, 0 );
						pFBXMesh->GetPolygonVertexNormal( i, j, normal );

						lpUnskinnedVertex & v = unskinnedVertexList[i * 3 + j];

						if ( normal[0] != 0 || normal[1] != 0 || normal[0] != 0 )
							spMesh->m_bNormalsPresent = true;

						v.normal.x = normal[0];
						v.normal.y = normal[1];
						v.normal.z = normal[2];

						normalizeInSitu( v.normal );

					}

				}
				break;
			}
			default:
				break; // other reference modes not shown here!
			}
		} // else

	}



	for ( int i = 0; i < pFBXMesh->GetLayerCount( ); i++ )
	{

		FbxLayer * pLayer = pFBXMesh->GetLayer( i );
		if ( pLayer == NULL )
			continue;

		LoadTextureCoordinatesFromLayer( spMesh, pFBXMesh, pLayer );

	}




	return true;

}

void FBXImporter::ProcessLightNode( )
{
}

void FBXImporter::ProcessCameraNode( )
{
}