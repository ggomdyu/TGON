#pragma once

#include "AnimBase.h"

class CFBXAnimation : public IAnimBase
{
public:
	CFBXAnimation( );
	~CFBXAnimation( );

	virtual void PlayAnim( ) override;

public:
	virtual void LoadAnim( FbxNode* pRootNode ) override;
};

