#pragma once
/*
* �ۼ��� : ����ȣ
* �ۼ��� : 2015-11-12
* ���� ���� :
* ���� ������ :
*/

#ifndef TGON_USE_PRECOMPILED_HEADER
	#include "Singleton.h"


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
public:
	explicit FBXImporter( _In_ const char* fbxFilepath = nullptr );
	~FBXImporter( );

	void ReadFBX( _In_ const char* fbxFilepath );

private:
	//void InitializeFBXInterface( );

	/*
		�� First - Load FbxScene which contains nodes
	*/
	void LoadScene( _In_ const char* fbxFilepath );

	void ProcessScene( int poseIndex = -1 );
	void ProcessNodeRecursive( FbxNode*, FbxPose*, FbxFrame* );
	void ProcessNode( FbxNode*, FbxPose*, FbxFrame* ); /* Find outted node */

	void SetNodeProperties( FbxNode*, FbxPose*, FbxFrame* );

	/*
		�� Second - 
	*/
	void ProcessMeshNode( FbxNode*, FbxPose*, FbxFrame* );
	void ProcessLightNode( );
	void ProcessCameraNode( );

	/*
		�� Third
	*/
	bool CreateMeshObject( FbxFrame* fbxFrame, FbxNode* fbxNode/*, NodeToFrameMap & nodeToFrameMap*/ );

private:
	FbxScene* m_fbxScene;
	FbxImporter* m_fbxImporter;
	std::unordered_map<FbxNode*, FbxFrame*> m_fbxFrameContainer;

	FbxMesh* m_fbxMesh;
	FbxFrame* m_fbxRootFrame;
};