#pragma once
class GraphicsInterface
{
public:
	GraphicsInterface( );
	~GraphicsInterface( );

	virtual void Initialize( ) = 0;

	virtual void BeginDraw( ) = 0;
	virtual void EndDraw( ) = 0;
};

