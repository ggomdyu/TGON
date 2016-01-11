#pragma once
/*
* 작성자 : 차준호
* 작성일 : 2015-11-12
* 최종 수정 :
* 최종 수정일 :
*/

#ifndef TGON_USE_PRECOMPILED_HEADER
	#include "Singleton.h"

	#include <unordered_set>

	#include <fbxsdk.h>
	#include "msgstream.h"
#endif

	#include <unordered_map>
#include "FbxFrame.h"

class FBX : public CSingleton<FBX>
{
public:
	FBX( );
	~FBX( );

	FbxManager* GetFbxManager( ) const { return m_fbxManager; }

private:
	FbxManager* m_fbxManager;
	FbxIOSettings* m_fbxIOSettings;
};

class FBXImporter
{
private:
	typedef std::vector<std::unordered_set<int>> ControlPointRemap;

public:
	explicit FBXImporter( _In_ const char* fbxFilepath = nullptr );
	~FBXImporter( );

	void ReadFBX( _In_ const char* fbxFilepath );

private:
	//void InitializeFBXInterface( );

	/*
		※ First - Load FbxScene which contains nodes
	*/
	void LoadScene( _In_ const char* fbxFilepath );

	void ProcessScene( int poseIndex = -1 );
	void ProcessNodeRecursive( FbxNode*, FbxPose*, FbxFrame* );  /* Find out node */
	void ProcessNode( FbxNode*, FbxPose*, FbxFrame* ); /* Found out */

	void SetNodeProperties( FbxNode*, FbxPose*, FbxFrame* );

	/*
		※ Second - 
	*/
	void ProcessMeshNode( FbxNode*, FbxPose*, FbxFrame* );
	void ProcessLightNode( );
	void ProcessCameraNode( );

	/*
		※ Third
	*/
	bool CreateMeshObject( FbxFrame* fbxFrame, FbxNode* fbxNode/*, NodeToFrameMap & nodeToFrameMap*/ );
	void LoadGeometryFromNode( /*spFBXMesh& spMesh, */FbxNode* pNode, FbxFrame* pFrame,
											ControlPointRemap& controlPointRemap );

private:
	FbxScene* m_fbxScene;
	FbxImporter* m_fbxImporter;
	std::unordered_map<FbxNode*, FbxFrame*> m_fbxFrameContainer;

	FbxMesh* m_fbxMesh;
	FbxFrame* m_fbxRootFrame;
};