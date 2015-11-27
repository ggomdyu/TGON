#pragma once

#include "stdafx.h"

class IAnimBase
{
public:
	IAnimBase( );
	~IAnimBase( );

	virtual void PlayAnim( ) = 0;

public:
	virtual void LoadAnim( FbxNode* pRootNode ) = 0;
	//virtual bool isEnd( ) = 0; // -> ���߿� �ʿ����� ������ ?
};

