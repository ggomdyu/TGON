#pragma once
#include "GraphicsInterface.h"

class Direct3Dt : public GraphicsInterface
{
public:
	Direct3Dt( );
	~Direct3Dt( );

	virtual void BeginDraw( ) override;
	virtual void EndDraw( ) override;
};

